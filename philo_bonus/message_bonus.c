/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:31:16 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 10:54:51 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_simul *simul, int type)
{
	t_philo	*philo;
	size_t	formatted_time;

	philo = simul->this_philo;
	formatted_time = get_current_time() - *philo->start_time;
	if (formatted_time < 0)
		formatted_time = 0;
	sem_wait(simul->mess_sem);
	if (!get_is_simul_over(simul))
	{
		if (type == 0)
			printf("%zu %d has taken a fork\n", formatted_time, philo->id);
		else if (type == 1)
			printf("%zu %d is eating\n", formatted_time, philo->id);
		else if (type == 2)
			printf("%zu %d is sleeping\n", formatted_time, philo->id);
		else if (type == 3)
			printf("%zu %d is thinking\n", formatted_time, philo->id);
	}
	if (type == 4)
	{
		set_is_simul_over(simul);
		printf("\r%zu %d died  ", formatted_time, philo->id);
	}
	sem_post(simul->mess_sem);
}
