/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_over_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:17:41 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 08:39:45 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_over(void *arg)
{
	t_simul	*simul;

	simul = (t_simul *)arg;
	sem_wait(simul->is_over_sem);
	sem_post(simul->is_over_sem);
	set_is_simul_over(simul);
	return (NULL);
}

int	get_is_simul_over(t_simul *simul)
{
	int	is_simul_over;

	sem_wait(simul->check_sem_1);
	is_simul_over = simul->is_simul_over;
	sem_post(simul->check_sem_1);
	return (is_simul_over);
}

void	set_is_simul_over(t_simul *simul)
{
	sem_wait(simul->check_sem_1);
	simul->is_simul_over = 1;
	sem_post(simul->check_sem_1);
}

int	get_is_check_over(t_simul *simul)
{
	int	is_check_over;

	sem_wait(simul->check_sem_2);
	is_check_over = simul->is_check_over;
	sem_post(simul->check_sem_2);
	return (is_check_over);
}

void	set_is_check_over(t_simul *simul)
{
	sem_wait(simul->check_sem_2);
	simul->is_check_over = 1;
	sem_post(simul->check_sem_2);
}
