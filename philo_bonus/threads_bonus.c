/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:28:33 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 08:53:30 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dead(void *arg)
{
	t_simul	*simul;

	simul = (t_simul *)arg;
	while (!get_is_simul_over(simul))
	{
		sem_wait(simul->meal_sem);
		if ((size_t)simul->params->time_to_die
			<= get_current_time() - simul->this_philo->last_meal)
		{
			sem_post(simul->meal_sem);
			print_message(simul, 4);
			sem_wait(simul->dead_sem);
			return (NULL);
		}
		sem_post(simul->meal_sem);
		usleep(50);
	}
	return (NULL);
}

void	eat(t_simul *simul)
{
	sem_wait(simul->forks);
	print_message(simul, 0);
	if (simul->params->philos_amount == 1)
	{
		while (!get_is_simul_over(simul))
			usleep(50);
		return ;
	}
	sem_wait(simul->forks);
	print_message(simul, 0);
	print_message(simul, 1);
	sem_wait(simul->meal_sem);
	simul->this_philo->last_meal = get_current_time();
	sem_post(simul->meal_sem);
	ft_usleep(simul->params->time_to_eat, simul);
	sem_wait(simul->meal_sem);
	(simul->this_philo->meals_eaten)++;
	if (simul->params->meals_req && simul->this_philo->meals_eaten
		== simul->params->meals_req)
		sem_wait(simul->meals_count_sem);
	sem_post(simul->meal_sem);
	sem_post(simul->forks);
	sem_post(simul->forks);
}

void	*exist(void *arg)
{
	t_simul	*simul;

	simul = (t_simul *)arg;
	simul->start_time = get_current_time();
	while (!get_is_simul_over(simul))
	{
		if (simul->this_philo->id % 2 == 0)
			ft_usleep(simul->params->time_to_think, simul);
		eat(simul);
		print_message(simul, 2);
		ft_usleep(simul->params->time_to_sleep, simul);
		print_message(simul, 3);
		if (simul->this_philo->id % 2)
			ft_usleep(simul->params->time_to_think, simul);
	}
	return (NULL);
}

void	launch_threads(t_simul *simul)
{
	simul->start_time = get_current_time();
	if (pthread_create(&simul->this_philo->existing_thread, NULL, exist,
			(void *)simul) != 0)
		clean_all_resources(simul, 1);
	if (pthread_create(&simul->this_philo->check_dead_thread, NULL,
			check_dead, (void *)simul) != 0)
		clean_all_resources(simul, 1);
	if (pthread_create(&simul->this_philo->check_over_thread, NULL,
			check_over, (void *)simul) != 0)
		clean_all_resources(simul, 1);
	pthread_join(simul->this_philo->existing_thread, NULL);
	pthread_join(simul->this_philo->check_dead_thread, NULL);
	pthread_join(simul->this_philo->check_over_thread, NULL);
}
