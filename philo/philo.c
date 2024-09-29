/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:53:54 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 10:00:28 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_simul *simul)
{
	if (pthread_mutex_init(&simul->dead_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&simul->meal_lock, NULL) != 0)
		return (pthread_mutex_destroy(&simul->dead_lock), 0);
	if (pthread_mutex_init(&simul->message_lock, NULL) != 0)
		return (pthread_mutex_destroy(&simul->dead_lock),
			pthread_mutex_destroy(&simul->meal_lock), 0);
	return (1);
}

void	destroy_mutexes(t_simul *simul)
{
	pthread_mutex_destroy(&simul->dead_lock);
	pthread_mutex_destroy(&simul->meal_lock);
	pthread_mutex_destroy(&simul->message_lock);
}

int	main(int argc, char **argv)
{
	t_simul		simul;
	t_params	params;

	if (!parse_args(argc, argv, &params))
		return (printf("Error\n"), 1);
	simul.is_philo_dead = 0;
	if (!init_mutexes(&simul))
		return (printf("Error\n"), 1);
	simul.philos = create_philos(&simul, &params);
	if (!simul.philos)
		return (destroy_mutexes(&simul), printf("Error\n"), 1);
	if (!launch_threads(&simul))
		return (destroy_mutexes(&simul), printf("Error\n"), 1);
	destroy_mutexes(&simul);
	free_philosophers(simul.philos);
	return (0);
}
