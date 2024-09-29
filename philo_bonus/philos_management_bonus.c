/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_management_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:13:49 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/22 13:43:59 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*new_philo(t_simul *simul, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->pid = 0;
	philo->id = id;
	philo->meals_eaten = 0;
	philo->start_time = &simul->start_time;
	philo->last_meal = get_current_time();
	return (philo);
}

t_philo	**create_philos(t_simul *simul)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc((simul->params->philos_amount + 1) * sizeof(t_philo *));
	if (!philos)
		return (NULL);
	while (i < simul->params->philos_amount)
	{
		philos[i] = new_philo(simul, i + 1);
		if (!philos[i])
			return (free_tab((void **)philos, i), NULL);
		i++;
	}
	return (philos[i] = NULL, philos);
}
