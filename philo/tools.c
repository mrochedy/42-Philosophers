/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:17:25 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 12:41:08 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_tab(void **tab, int n)
{
	int	i;

	if (!tab || !(*tab))
		return ;
	i = 0;
	if (n != -1)
	{
		while (i < n)
			free(tab[i++]);
	}
	else
		while (tab[i])
			free(tab[i++]);
	free(tab);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("gettimeofday() error\n"), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	if (milliseconds > 0)
	{
		start = get_current_time();
		while ((get_current_time() - start) < milliseconds)
		{
			if (get_is_dead(philo))
				return ;
			usleep(500);
		}
	}
}

void	print_message(t_philo *philo, int type)
{
	size_t	formatted_time;

	formatted_time = get_current_time() - *philo->start_time;
	if (formatted_time < 0)
		formatted_time = 0;
	pthread_mutex_lock(philo->message_lock);
	if (!get_is_dead(philo))
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
	else if (type == 4)
		printf("%zu %d died\n", formatted_time, philo->id);
	pthread_mutex_unlock(philo->message_lock);
}
