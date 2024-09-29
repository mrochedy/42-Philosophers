/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:20:20 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 12:41:23 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->dead_lock);
	is_dead = *philo->is_philo_dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (is_dead);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(philo->meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	return (last_meal);
}

int	get_meals_eaten(t_philo *philo)
{
	int	meals_eaten;

	pthread_mutex_lock(philo->meal_lock);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(philo->meal_lock);
	return (meals_eaten);
}
