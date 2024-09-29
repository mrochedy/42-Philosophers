/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:13:49 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/19 14:16:48 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_mutexes_to_philo(t_philo *philo, t_simul *simul)
{
	philo->dead_lock = &simul->dead_lock;
	philo->meal_lock = &simul->meal_lock;
	philo->message_lock = &simul->message_lock;
}

t_philo	*new_philo(t_simul *simul, t_params *params, int id,
	pthread_mutex_t **forks)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->is_philo_dead = &simul->is_philo_dead;
	philo->start_time = &simul->start_time;
	philo->params = params;
	philo->last_meal = get_current_time();
	add_mutexes_to_philo(philo, simul);
	philo->l_fork = forks[0];
	if (params->philos_amount != 1)
		philo->r_fork = forks[1];
	else
		philo->r_fork = NULL;
	return (philo);
}

t_philo	**create_philos(t_simul *simul, t_params *params)
{
	int				i;
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*two_forks[2];

	i = 0;
	philos = malloc((params->philos_amount + 1) * sizeof(t_philo *));
	if (!philos)
		return (NULL);
	forks = create_forks(params->philos_amount);
	if (!forks)
		return (free(philos), NULL);
	while (i < params->philos_amount)
	{
		two_forks[0] = forks[i];
		two_forks[1] = forks[0];
		if (i + 1 < params->philos_amount)
			two_forks[1] = forks[i + 1];
		philos[i] = new_philo(simul, params, i + 1, two_forks);
		if (!philos[i])
			return (destroy_forks(forks, -1), free_tab((void **)philos, i),
				NULL);
		i++;
	}
	return (philos[i] = NULL, free(forks), philos);
}

void	free_philosophers(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_mutex_destroy(philos[i]->l_fork);
		free(philos[i]->l_fork);
		free(philos[i++]);
	}
	free(philos);
}
