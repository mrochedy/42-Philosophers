/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:12:27 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/25 09:25:35 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi_check(const char *nptr)
{
	long	nbr;
	int		indexes[2];
	int		sign;

	nbr = 0;
	indexes[0] = 0;
	indexes[1] = 0;
	sign = 1;
	if (nptr[indexes[0]] == '+' || nptr[indexes[0]] == '-')
		if (!nptr[indexes[0] + 1])
			return (0);
	if (nptr[indexes[0]] == '+' || nptr[indexes[0]] == '-')
		if (nptr[indexes[0]++] == '-')
			sign = -1;
	while (nptr[indexes[0]] == '0')
		indexes[0]++;
	while (nptr[indexes[0]] >= '0' && nptr[indexes[0]] <= '9')
	{
		nbr = nbr * 10 + nptr[indexes[0]++] - '0';
		indexes[1]++;
	}
	if (nptr[indexes[0]] || indexes[1] > 10 || nbr * sign > 2147483647
		|| nbr * sign < -2147483648)
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -sign;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = nbr * 10 + nptr[i++] - '0';
	return (sign * nbr);
}

int	parse_args(int argc, char **argv, t_params *params)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
		if (!ft_atoi_check(argv[i++]))
			return (0);
	params->philos_amount = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->time_to_think = params->time_to_die
		- (params->time_to_eat + params->time_to_sleep) - 5;
	if (params->time_to_think <= 0)
		params->time_to_think = 0;
	params->meals_req = 0;
	if (argc == 6)
		params->meals_req = ft_atoi(argv[5]);
	if (params->philos_amount <= 0 || params->time_to_die <= 0
		|| params->time_to_eat <= 0 || params->time_to_sleep <= 0
		|| (argc == 6 && params->meals_req <= 0) || params->philos_amount > 200)
		return (0);
	return (1);
}
