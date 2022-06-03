/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3c_philos_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:15:32 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/03 09:17:05 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_we_done_yet(t_philo *p)
{
	pthread_mutex_lock(&p->god->check_death);
	if (p->god->end == YES)
		return (pthread_mutex_unlock(&p->god->check_death), YES);
	pthread_mutex_unlock(&p->god->check_death);
	if (p->eaten == p->god->nb_meals)
		return (YES);
	return (NO);
}

static int	take_forks(t_philo *p)
{
	if (p->i_am % 2 == 0)
	{
		pthread_mutex_lock(&p->fork);
		if (are_we_done_yet(p) == YES)
			return (pthread_mutex_unlock(&p->fork), YES);
		pthread_mutex_lock(p->nxt_fork);
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(p->nxt_fork);
		if (are_we_done_yet(p) == YES)
			return (pthread_mutex_unlock(p->nxt_fork), YES);
		pthread_mutex_lock(&p->fork);
	}
	ft_print(p, "has taken a fork");
	ft_print(p, "has taken a fork");
	ft_print(p, "is eating");
	return (EXIT_SUCCESS);
}

static int	crunch_crunch(t_philo *p)
{
	if (take_forks(p) == YES)
		return (ERROR);
	pthread_mutex_lock(&p->god->check_meals);
	p->eaten++;
	pthread_mutex_unlock(&p->god->check_meals);
	if (paranoid_usleep(p->god, p->god->time_eat) == ERROR)
		return (pthread_mutex_unlock(&p->fork),
			pthread_mutex_unlock(p->nxt_fork), ERROR);
	pthread_mutex_unlock(&p->fork);
	pthread_mutex_unlock(p->nxt_fork);
	pthread_mutex_lock(&p->god->check_meals);
	p->time_last_meal = get_time(p->god->time_start, TIMESTAMP);
	pthread_mutex_unlock(&p->god->check_meals);
	return (EXIT_SUCCESS);
}

int	eat_sleep_think(t_philo *p)
{
	if (!p)
		return (ERROR);
	while (1)
	{
		if (are_we_done_yet(p) == YES)
			return (ERROR);
		if (crunch_crunch(p) == ERROR)
			return (ERROR);
		if (are_we_done_yet(p) == YES)
			return (ERROR);
		ft_print(p, "is sleeping");
		if (paranoid_usleep(p->god, p->god->time_sleep) == ERROR)
			return (ERROR);
		if (are_we_done_yet(p) == YES)
			return (ERROR);
		ft_print(p, "is thinking");
	}
	return (ERROR);
}
