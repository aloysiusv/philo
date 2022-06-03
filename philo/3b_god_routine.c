/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3b_god_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:15:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/03 09:00:05 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	did_someone_die(t_all *g)
{
	size_t	i;
	size_t	last_meal;

	i = 0;
	while (i < g->nb_philo)
	{
		pthread_mutex_lock(&g->check_meals);
		last_meal
			= get_time(g->time_start, TIMESTAMP) - g->philos[i].time_last_meal;
		pthread_mutex_unlock(&g->check_meals);
		if (last_meal > g->time_die)
		{
			ft_print(&g->philos[i], "died");
			pthread_mutex_lock(&g->check_death);
			g->end = YES;
			pthread_mutex_unlock(&g->check_death);
			return (YES);
		}
		i++;
	}
	return (NO);
}

int	did_everyone_eat(t_all *g)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < g->nb_philo)
	{
		pthread_mutex_lock(&g->check_meals);
		if (g->philos[i].eaten == g->nb_meals)
			count++;
		if (count == g->nb_philo)
		{
			pthread_mutex_lock(&g->check_death);
			g->end = YES;
			pthread_mutex_unlock(&g->check_death);
			pthread_mutex_unlock(&g->check_meals);
			return (YES);
		}
		pthread_mutex_unlock(&g->check_meals);
		i++;
	}
	return (NO);
}
