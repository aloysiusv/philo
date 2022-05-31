/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:26:41 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/31 21:21:21 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_timestamp(size_t milli_start)
{
	struct timeval	tv;
	size_t			milli_now;

	gettimeofday(&tv, NULL);
	milli_now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (milli_now - milli_start);
}

void	free_tabs(t_all *g)
{
	if (g->philos)
		free(g->philos);
}

int	paranoid_usleep(t_philo *p, size_t time_to_pause)
{
	size_t	start;
	size_t	current;

	start = get_start_time();
	current = get_start_time();
	while (current - start < time_to_pause)
	{
		current = get_start_time();
		if (p->god->end == YES)
		{
			pthread_mutex_unlock(&p->fork);
			pthread_mutex_unlock(p->nxt_fork);
			return (ERROR);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_print(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->god->check_death);
	if (p->god->end == NO)
	{
		if (pthread_mutex_lock(&p->god->writing) != 0)
			return(pthread_mutex_unlock(&p->god->check_death), ERROR);
		printf("%zums philo %zu %s\n",
				get_timestamp(p->god->time_start), p->i_am, str);
		if (pthread_mutex_unlock(&p->god->writing) != 0)
			return(pthread_mutex_unlock(&p->god->check_death), ERROR);
	}
	pthread_mutex_unlock(&p->god->check_death);
	return (EXIT_SUCCESS);
}

int	oops_crash(t_all *g, char *error)
{
	free_tabs(g);
	printf("%s\n", error);
	return (EXIT_FAILURE);
}