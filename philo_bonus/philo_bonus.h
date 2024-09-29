/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:02:05 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 13:51:24 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# define DEAD_SEM "/dead_semaphore"
# define IS_OVER_SEM "/is_over_semaphore"
# define CHECK_SEM_1 "/check_semaphore_1"
# define CHECK_SEM_2 "/check_semaphore_2"
# define MEAL_SEM "/meal_semaphore"
# define MEALS_COUNT_SEM "/meals_count_semaphore"
# define MESS_SEM "/messages_semaphore"
# define FORKS_SEM "/forks_semaphore"

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
	pthread_t	existing_thread;
	pthread_t	check_dead_thread;
	pthread_t	check_over_thread;
	pid_t		pid;
	int			id;
	int			meals_eaten;
	size_t		last_meal;
	size_t		*start_time;
}	t_philo;

typedef struct s_simul
{
	size_t		start_time;
	t_philo		**philos;
	t_philo		*this_philo;
	pthread_t	check_full_sem;
	sem_t		*forks;
	sem_t		*dead_sem;
	sem_t		*is_over_sem;
	sem_t		*check_sem_1;
	sem_t		*check_sem_2;
	sem_t		*meals_count_sem;
	sem_t		*meal_sem;
	sem_t		*mess_sem;
	t_params	*params;
	int			is_simul_over;
	int			is_check_over;
}	t_simul;

int		parse_args(int argc, char **argv, t_params *params);
t_philo	**create_philos(t_simul *simul);
int		launch_processes(t_simul *simul);
void	kill_processes(t_simul *simul);
void	launch_threads(t_simul *simul);
void	*check_over(void *arg);
void	print_message(t_simul *simul, int type);
void	ft_usleep(size_t milliseconds, t_simul *simul);
size_t	get_current_time(void);
void	free_tab(void **tab, int n);
void	close_semaphores(t_simul *simul);
void	clean_all_resources(t_simul *simul, int code);
int		get_is_simul_over(t_simul *simul);
void	set_is_simul_over(t_simul *simul);
int		get_is_check_over(t_simul *simul);
void	set_is_check_over(t_simul *simul);

#endif
