/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:30:33 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 09:30:09 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_full_dead_sem(void *arg)
{
	t_simul	*simul;
	int		i;
	int		j;

	simul = (t_simul *)arg;
	i = 0;
	while (!get_is_check_over(simul) && i < 20)
	{
		usleep(50);
		i++;
	}
	if (!get_is_check_over(simul))
	{
		simul->is_simul_over = 1;
		j = 0;
		while (j++ < simul->params->philos_amount + 1)
			sem_post(simul->dead_sem);
	}
	return (NULL);
}

void	*check_full_meals_sem(void *arg)
{
	t_simul	*simul;
	int		i;
	int		j;

	simul = (t_simul *)arg;
	i = 0;
	while (!get_is_check_over(simul) && i < 20)
	{
		usleep(50);
		i++;
	}
	if (!get_is_check_over(simul))
	{
		simul->is_simul_over = 1;
		j = 0;
		while (j++ < simul->params->philos_amount + 1)
			sem_post(simul->meals_count_sem);
	}
	return (NULL);
}

void	simul_not_over_case(t_simul *simul, sem_t *sem, pthread_t *thread)
{
	set_is_check_over(simul);
	sem_post(sem);
	pthread_join(*thread, NULL);
}

void	*main_process(t_simul *simul)
{
	pthread_t	thread;

	while (!get_is_simul_over(simul))
	{
		simul->is_check_over = 0;
		pthread_create(&thread, NULL, check_full_dead_sem, (void *)simul);
		sem_wait(simul->dead_sem);
		if (!simul->is_simul_over)
			simul_not_over_case(simul, simul->dead_sem, &thread);
		else
			return (pthread_join(thread, NULL), sem_post(simul->is_over_sem),
				usleep(1000000), printf("\n"), NULL);
		simul->is_check_over = 0;
		pthread_create(&thread, NULL, check_full_meals_sem, (void *)simul);
		sem_wait(simul->meals_count_sem);
		if (!simul->is_simul_over)
			simul_not_over_case(simul, simul->meals_count_sem, &thread);
		else
			return (pthread_join(thread, NULL), sem_post(simul->is_over_sem),
				usleep(1000000), NULL);
	}
	return (sem_post(simul->is_over_sem), usleep(1000000), NULL);
}

int	launch_processes(t_simul *simul)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 1;
	simul->this_philo = NULL;
	while (pid && simul->philos[i])
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid)
			simul->philos[i]->pid = pid;
		else
			simul->this_philo = simul->philos[i];
		i++;
	}
	if (simul->this_philo)
		launch_threads(simul);
	else
		main_process(simul);
	return (1);
}
