/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:39:35 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 12:42:02 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_simul *simul)
{
	pthread_mutex_lock(&simul->dead_lock);
	simul->is_philo_dead = 1;
	pthread_mutex_unlock(&simul->dead_lock);
}

void	*is_philo_dead(void *arg)
{
	t_simul	*simul;
	int		i;
	int		have_eaten_enough;

	simul = (t_simul *)arg;
	while (1)
	{
		i = 0;
		have_eaten_enough = 1;
		while (simul->philos[i])
		{
			if ((size_t)simul->philos[i]->params->time_to_die
				<= get_current_time() - get_last_meal(simul->philos[i]))
				return (die(simul),
					print_message(simul->philos[i], 4), NULL);
			if (get_meals_eaten(simul->philos[i])
				< simul->philos[i]->params->meals_req)
				have_eaten_enough = 0;
			i++;
		}
		if (have_eaten_enough && simul->philos[0]->params->meals_req)
			return (die(simul), NULL);
	}
}

void	*eat(t_philo *philo)
{
	take_first_fork(philo);
	print_message(philo, 0);
	if (!philo->r_fork)
		return (ft_usleep(philo->params->time_to_die, philo),
			pthread_mutex_unlock(philo->l_fork), NULL);
	take_second_fork(philo);
	print_message(philo, 0);
	print_message(philo, 1);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->params->time_to_eat, philo);
	pthread_mutex_lock(philo->meal_lock);
	(philo->meals_eaten)++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	*exist(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_is_dead(philo))
			return (NULL);
		eat(philo);
		print_message(philo, 2);
		ft_usleep(philo->params->time_to_sleep, philo);
		print_message(philo, 3);
		ft_usleep(philo->params->time_to_think, philo);
	}
	return (NULL);
}

int	launch_threads(t_simul *simul)
{
	int	i;

	i = 0;
	simul->start_time = get_current_time();
	while (simul->philos[i])
	{
		if (pthread_create(&simul->philos[i]->thread, NULL, exist,
				(void *)simul->philos[i]) != 0)
			return (free_philosophers(simul->philos), 0);
		i++;
	}
	if (pthread_create(&simul->dead_thread, NULL, is_philo_dead,
			(void *)simul) != 0)
		return (free_philosophers(simul->philos), 0);
	i = 0;
	while (simul->philos[i])
		pthread_join(simul->philos[i++]->thread, NULL);
	pthread_join(simul->dead_thread, NULL);
	return (1);
}
