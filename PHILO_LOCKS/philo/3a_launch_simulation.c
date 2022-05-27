/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_launch_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:16:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/27 02:27:33 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	crunch_crunch(t_all *g)
{
	
}

static void	*philosophize(void *all)
{
	t_all		*g;
	pthread_t	god;

	g = (t_all *)all;
	if (!g->philos)
		return (NULL);
	if (pthread_create(&god, NULL, &god_routine, &g))
		return (NULL);
	while (g->one_died == NO)
	{
		if (crunch_crunch(p) == ERROR)
			return (NULL);
		if (p->nb_meals > 0 && p->eaten == p->nb_meals)
		{
			p->all_meals_done = YES;
			return (NULL);
		}
		if (p->died == NO && p->all_meals_done == NO)
		{
			printf("%zums philo %zu is sleeping\n",
				get_now(p->time_start), p->i_am);
			usleep(p->time_sleep * 1000);
			if (p->died == NO && p->all_meals_done == NO)
				printf("%zums philo %zu is thinking\n",
					get_now(p->time_start), p->i_am);
		}
	}
	if (pthread_detach(&god) != 0)
		return (NULL);
	return (NULL);
}

int	launch_simulation(t_all *g)
{
	size_t		i;
	pthread_t	philos;

	i = 0;
	while (i < g->nb_philo)
	{
		if (pthread_create(&philos, NULL, &philosophize, &g->philos[i]) != 0)
			return (ERROR);
		i++;
	}
	i = 0;
	while (i < g->nb_philo)
		if (pthread_join(&philos, NULL) != 0)
			return (ERROR);
	i = 0;
	while (i < g->nb_philo)
		pthread_mutex_destroy(&g->forks[i++]);
	pthread_mutex_destroy(g->writing);
	return (EXIT_SUCCESS);
}
