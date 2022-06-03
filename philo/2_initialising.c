/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_initialising.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:09:33 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/03 09:08:34 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_all *g)
{
	size_t	i;

	i = 0;
	while (i < g->nb_philo)
		if (pthread_mutex_init(&g->philos[i++].fork, NULL) != 0)
			return (oops_crash(g, "error: philo: failed mutex_init"));
	if (pthread_mutex_init(&g->writing, NULL) != 0)
		return (oops_crash(g, "error: philo: failed mutex_init"));
	if (pthread_mutex_init(&g->check_death, NULL) != 0)
		return (oops_crash(g, "error: philo: failed mutex_init"));
	if (pthread_mutex_init(&g->check_meals, NULL) != 0)
		return (oops_crash(g, "error: philo: failed mutex_init"));
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

int	initialising(t_all *g, char *argv[])
{
	size_t	start;

	g->nb_philo = ft_atol(argv[1]);
	g->time_die = ft_atol(argv[2]);
	g->time_die = ft_atol(argv[2]);
	g->time_eat = ft_atol(argv[3]);
	g->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		g->nb_meals = ft_atol(argv[5]);
	else
		g->nb_meals = -1;
	start = get_time(0, CURRENT_TIME);
	if (!start)
		return (ERROR);
	g->time_start = start;
	if (init_philo_tab(g) == ERROR)
		return (ERROR);
	if (init_mutexes(g) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}
