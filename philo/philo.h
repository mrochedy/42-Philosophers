/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:02:05 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 12:48:01 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_params
{
	int	philos_amount;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
	int	meals_req;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				*is_philo_dead;
	size_t			last_meal;
	size_t			*start_time;
	t_params		*params;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*message_lock;
}	t_philo;

typedef struct s_simul
{
	pthread_t		dead_thread;
	int				is_philo_dead;
	size_t			start_time;
	t_philo			**philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	message_lock;
}	t_simul;

int				parse_args(int argc, char **argv, t_params *params);
pthread_mutex_t	**create_forks(int nb);
void			destroy_forks(pthread_mutex_t **forks, int n);
void			take_first_fork(t_philo *philo);
void			take_second_fork(t_philo *philo);
t_philo			**create_philos(t_simul *simul, t_params *params);
void			free_philosophers(t_philo **philos);
int				launch_threads(t_simul *simul);
void			free_tab(void **tab, int n);
size_t			get_current_time(void);
void			ft_usleep(size_t milliseconds, t_philo *philo);
void			print_message(t_philo *philo, int type);
int				get_is_dead(t_philo *philo);
size_t			get_last_meal(t_philo *philo);
int				get_meals_eaten(t_philo *philo);

#endif
