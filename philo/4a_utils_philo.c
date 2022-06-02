/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:26:41 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/02 21:51:37 by lrandria         ###   ########.fr       */
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

int	ft_print(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->god->check_death);
	if (p->god->end == NO)
	{
		pthread_mutex_lock(&p->god->writing);
		printf("%zums philo %zu %s\n",
			get_timestamp(p->god->time_start), p->i_am, str);
		pthread_mutex_unlock(&p->god->writing);
	}
	pthread_mutex_unlock(&p->god->check_death);
	return (EXIT_SUCCESS);
}

void	free_tabs(t_all *g)
{
	if (g->philos)
		free(g->philos);
}

int	oops_crash(t_all *g, char *error)
{
	free_tabs(g);
	printf("%s\n", error);
	return (ERROR);
}
