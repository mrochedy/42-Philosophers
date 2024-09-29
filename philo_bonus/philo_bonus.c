/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:53:54 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 09:24:36 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	close_and_unlink_semaphore(sem_t *sem, char *name)
{
	if (sem && sem != SEM_FAILED)
		if (sem_close(sem) != 0)
			return (0);
	sem_unlink(name);
	return (1);
}

void	close_semaphores(t_simul *simul)
{
	if (!close_and_unlink_semaphore(simul->dead_sem, DEAD_SEM))
		return ;
	if (!close_and_unlink_semaphore(simul->meal_sem, MEAL_SEM))
		return ;
	if (!close_and_unlink_semaphore(simul->meals_count_sem, MEALS_COUNT_SEM))
		return ;
	if (!close_and_unlink_semaphore(simul->check_sem_1, CHECK_SEM_1))
		return ;
	if (!close_and_unlink_semaphore(simul->check_sem_2, CHECK_SEM_2))
		return ;
	if (!close_and_unlink_semaphore(simul->is_over_sem, IS_OVER_SEM))
		return ;
	if (!close_and_unlink_semaphore(simul->mess_sem, MESS_SEM))
		return ;
	if (!close_and_unlink_semaphore(simul->forks, FORKS_SEM))
		return ;
}

int	open_semaphores(t_simul *simul, t_params *params)
{
	simul->dead_sem = sem_open(DEAD_SEM, O_CREAT, 0644, 1);
	if (simul->dead_sem == SEM_FAILED)
		return (0);
	simul->meal_sem = sem_open(MEAL_SEM, O_CREAT, 0644, 1);
	if (simul->meal_sem == SEM_FAILED)
		return (close_semaphores(simul), 0);
	simul->meals_count_sem = sem_open(MEALS_COUNT_SEM, O_CREAT, 0644,
			params->philos_amount);
	if (simul->meals_count_sem == SEM_FAILED)
		return (close_semaphores(simul), 0);
	simul->is_over_sem = sem_open(IS_OVER_SEM, O_CREAT, 0644, 1);
	if (simul->is_over_sem == SEM_FAILED)
		return (close_semaphores(simul), 0);
	sem_wait(simul->is_over_sem);
	simul->check_sem_1 = sem_open(CHECK_SEM_1, O_CREAT, 0644, 1);
	simul->check_sem_2 = sem_open(CHECK_SEM_2, O_CREAT, 0644, 1);
	if (simul->check_sem_1 == SEM_FAILED || simul->check_sem_2 == SEM_FAILED)
		return (close_semaphores(simul), 0);
	simul->mess_sem = sem_open(MESS_SEM, O_CREAT, 0644, 1);
	if (simul->mess_sem == SEM_FAILED)
		return (close_semaphores(simul), 0);
	simul->forks = sem_open(FORKS_SEM, O_CREAT, 0644, params->philos_amount);
	if (simul->forks == SEM_FAILED)
		return (close_semaphores(simul), 0);
	return (1);
}

void	try_open_semaphores(t_simul *simul)
{
	simul->dead_sem = sem_open(DEAD_SEM, 0);
	if (simul->dead_sem != SEM_FAILED)
		close_and_unlink_semaphore(simul->dead_sem, DEAD_SEM);
	simul->meal_sem = sem_open(MEAL_SEM, 0);
	if (simul->meal_sem != SEM_FAILED)
		close_and_unlink_semaphore(simul->meal_sem, MEAL_SEM);
	simul->is_over_sem = sem_open(IS_OVER_SEM, 0);
	if (simul->is_over_sem != SEM_FAILED)
		close_and_unlink_semaphore(simul->is_over_sem, IS_OVER_SEM);
	simul->check_sem_1 = sem_open(CHECK_SEM_1, 0);
	if (simul->check_sem_1 != SEM_FAILED)
		close_and_unlink_semaphore(simul->check_sem_1, CHECK_SEM_1);
	simul->check_sem_2 = sem_open(CHECK_SEM_2, 0);
	if (simul->check_sem_2 != SEM_FAILED)
		close_and_unlink_semaphore(simul->check_sem_2, CHECK_SEM_2);
	simul->meals_count_sem = sem_open(MEALS_COUNT_SEM, 0);
	if (simul->meals_count_sem != SEM_FAILED)
		close_and_unlink_semaphore(simul->meals_count_sem, MEALS_COUNT_SEM);
	simul->mess_sem = sem_open(MESS_SEM, 0);
	if (simul->mess_sem != SEM_FAILED)
		close_and_unlink_semaphore(simul->mess_sem, MESS_SEM);
	simul->forks = sem_open(FORKS_SEM, 0);
	if (simul->forks != SEM_FAILED)
		close_and_unlink_semaphore(simul->forks, FORKS_SEM);
}

int	main(int argc, char **argv)
{
	t_simul		simul;
	t_params	params;

	if (!parse_args(argc, argv, &params))
		return (printf("Error\n"), 1);
	try_open_semaphores(&simul);
	if (!open_semaphores(&simul, &params))
		return (printf("Error\n"), 1);
	simul.params = &params;
	simul.philos = create_philos(&simul);
	if (!simul.philos)
		return (close_semaphores(&simul), printf("Error\n"), 1);
	simul.is_simul_over = 0;
	if (!launch_processes(&simul))
		return (close_semaphores(&simul),
			free_tab((void **)simul.philos, -1), printf("Error\n"), 1);
	free_tab((void **)simul.philos, -1);
	close_semaphores(&simul);
	return (0);
}
