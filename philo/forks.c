/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:07:18 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/24 10:58:19 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
}

void	take_second_fork(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
}

void	destroy_forks(pthread_mutex_t **forks, int n)
{
	int	i;

	i = 0;
	if (n != -1)
	{
		while (i < n)
			pthread_mutex_destroy(forks[i++]);
	}
	else
		while (forks[i])
			pthread_mutex_destroy(forks[i++]);
	free_tab((void **)forks, n);
}

pthread_mutex_t	**create_forks(int nb)
{
	int				i;
	pthread_mutex_t	**forks;

	i = 0;
	forks = malloc((nb + 1) * sizeof(pthread_mutex_t *));
	if (!forks)
		return (NULL);
	while (i < nb)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (destroy_forks(forks, i), NULL);
		if (pthread_mutex_init(forks[i], NULL) != 0)
			return (destroy_forks(forks, i), free(forks[i]), NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}
