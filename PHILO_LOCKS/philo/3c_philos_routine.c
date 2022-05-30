/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3c_philos_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:15:32 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/31 00:20:20 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	crunch_crunch(t_philo *p, size_t tmp_end)
{
	if (!p)
		return (ERROR);
	if (tmp_end == NO)
	{
		pthread_mutex_lock(&p->fork);
		pthread_mutex_lock(p->nxt_fork);
		ft_print(p, "has taken a fork");
		ft_print(p, "has taken a fork");
		ft_print(p, "is eating");
		usleep(p->god->time_eat * 1000);
		pthread_mutex_lock(&p->god->check_meals);
		p->eaten++;
		pthread_mutex_unlock(&p->god->check_meals);
		pthread_mutex_unlock(p->nxt_fork);
		pthread_mutex_unlock(&p->fork);
		pthread_mutex_lock(&p->god->check_meals);
		p->time_last_meal = get_timestamp(p->god->time_start);
		pthread_mutex_unlock(&p->god->check_meals);
		// if (p->eaten == p->god->nb_meals)
		// 	return (ERROR);
	}
	return (EXIT_SUCCESS);
}

void	eat_sleep_think(t_philo *p)
{
	size_t	tmp_end;

	if (!p)
		return ;
	if (p->i_am % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&p->god->check_death);
	tmp_end = p->god->end;
	pthread_mutex_unlock(&p->god->check_death);
	while (tmp_end == NO)
	{
		pthread_mutex_lock(&p->god->check_death);
		tmp_end = p->god->end;
		pthread_mutex_unlock(&p->god->check_death);
		if (crunch_crunch(p, tmp_end) == ERROR)
			return ;
		ft_print(p, "is sleeping");
		usleep(p->god->time_sleep * 1000);
		ft_print(p, "thinking");
	}
	return ;
}
