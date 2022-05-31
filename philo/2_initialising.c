/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_initialising.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:09:33 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/31 22:06:07 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0') * sign;
		i++;
	}
	return (res);
}

static int	init_mutexes(t_all *g)
{
	size_t	i;

	i = 0;
	while (i < g->nb_philo)
		if (pthread_mutex_init(&g->philos[i++].fork, NULL) != 0)
			return (printf("Error init philos mutex\n"), ERROR);
	if (pthread_mutex_init(&g->writing, NULL) != 0)
		return (printf("Error init writing mutex\n"), ERROR);
	if (pthread_mutex_init(&g->check_death, NULL) != 0)
		return (printf("Error init check_death mutex\n"), ERROR);
	if (pthread_mutex_init(&g->check_meals, NULL) != 0)
		return (printf("Error init check_meals mutex\n"), ERROR);
	return (EXIT_SUCCESS);
}

static int	init_philo_tab(t_all *g)
{
	size_t	i;

	g->philos = (t_philo *)malloc(sizeof(t_philo) * g->nb_philo);
	if (!g->philos)
		return (ERROR);
	i = 0;
	while (i < g->nb_philo)
	{
		memset(&g->philos[i], 0, sizeof(t_philo));
		g->philos[i].i_am = i + 1;
		g->philos[i].eaten = 0;
		g->philos[i].time_last_meal = 0;
		g->philos[i].nxt_fork = &g->philos[(i + 1) % g->nb_philo].fork;
		g->philos[i].god = g;
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t	get_start_time(void)
{
	struct timeval	tv;
	size_t			start;

	if (gettimeofday(&tv, NULL) == ERROR)
		return (0);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (start);
}

int	initialising(t_all *g, char *argv[])
{
	size_t	start;

	g->nb_philo = ft_atoi(argv[1]);
	g->time_die = ft_atoi(argv[2]);
	g->time_eat = ft_atoi(argv[3]);
	g->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g->nb_meals = ft_atoi(argv[5]);
	else
		g->nb_meals = -1;
	start = get_start_time();
	if (!start)
		return (ERROR);
	g->time_start = start;
	if (init_philo_tab(g) == ERROR)
		return (ERROR);
	if (init_mutexes(g) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}
