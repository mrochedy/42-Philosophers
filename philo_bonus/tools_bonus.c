/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:17:25 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 07:58:23 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_usleep(size_t milliseconds, t_simul *simul)
{
	size_t	start;

	if (milliseconds > 0)
	{
		start = get_current_time();
		while ((get_current_time() - start) < milliseconds)
		{
			if (!get_is_simul_over(simul))
				usleep(500);
			else
				return ;
		}
	}
}

void	clean_all_resources(t_simul *simul, int code)
{
	free_tab((void **)simul->philos, -1);
	close_semaphores(simul);
	exit(code);
}
