/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3b_god_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:15:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/30 23:13:50 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_everyone(t_philo *p)
{
	size_t	i;

	i = 0;
	while (i < p->nb_philo)
	{
		p[i].died = YES;
		i++;
	}
}

static int	did_someone_die(t_philo *p)
{
	size_t	i;
	size_t	last_meal;

	i = 0;
	while (i < p->nb_philo)
	{
		last_meal = get_now(p->time_start) - p[i].time_last_meal;
		if (last_meal > p->time_die)
		{
			pthread_mutex_lock(p[i].action);
			p[i].died = YES;
			printf("%zu philo %zu died\n", get_now(p[i].time_start), p[i].i_am);
			kill_everyone(p);
			pthread_mutex_unlock(p[i].action);
			return (YES);
		}
		i++;
	}
	return (NO);
}

static int	did_everyone_eat(t_philo *p)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < p->nb_philo)
	{
		if (p[i].all_meals_done == YES)
			count++;
		if (count == p->nb_philo)
			return (YES);
		i++;
	}
	return (NO);
}

void	*god_routine(void *everyone)
{
	t_philo	*philos;

	philos = (t_philo *)everyone;
	if (!philos)
		return (NULL);
	while (1)
	{
		if (did_someone_die(philos) == YES)
			return (NULL);
		if (did_everyone_eat(philos) == YES)
			return (NULL);
	}
	return (NULL);
}
