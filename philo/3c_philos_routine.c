/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3c_philos_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:15:32 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/02 01:19:10 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ask_god_if_someone_died(t_philo *p)
{
	pthread_mutex_lock(&p->god->check_death);
	if (p->god->end == YES)
		return (pthread_mutex_unlock(&p->god->check_death), YES);
	pthread_mutex_unlock(&p->god->check_death);
	if (p->eaten == p->god->nb_meals)
		return (YES);
	return (NO);
}

static void	screw_you_norminette(t_philo *p)
{
	ft_print(p, "has taken a fork");
	ft_print(p, "has taken a fork");
	ft_print(p, "is eating");
}

static int	crunch_crunch(t_philo *p)
{
	if (!p)
		return (ERROR);
	if (p->i_am % 2 == 0)
	{
		pthread_mutex_lock(&p->fork);
		pthread_mutex_lock(p->nxt_fork);
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(p->nxt_fork);
		pthread_mutex_lock(&p->fork);
	}
	screw_you_norminette(p);
	usleep(p->god->time_eat * 1000);
	pthread_mutex_unlock(&p->fork);
	pthread_mutex_unlock(p->nxt_fork);
	pthread_mutex_lock(&p->god->check_meals);
	p->eaten++;
	pthread_mutex_unlock(&p->god->check_meals);
	pthread_mutex_lock(&p->god->check_meals);
	p->time_last_meal = get_timestamp(p->god->time_start);
	pthread_mutex_unlock(&p->god->check_meals);
	return (EXIT_SUCCESS);
}

int	eat_sleep_think(t_philo *p)
{
	if (!p)
		return (ERROR);
	while (1)
	{
		if (ask_god_if_someone_died(p) == YES)
			return (ERROR);
		if (crunch_crunch(p) == ERROR)
			return (ERROR);
		if (ask_god_if_someone_died(p) == YES)
			return (ERROR);
		ft_print(p, "is sleeping");
		usleep(p->god->time_sleep * 1000);
		if (ask_god_if_someone_died(p) == YES)
			return (ERROR);
		ft_print(p, "is thinking");
	}
	return (ERROR);
}
