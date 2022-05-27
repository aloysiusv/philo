/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:26:41 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/27 17:55:42 by lrandria         ###   ########.fr       */
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
	if (g->forks)
		free(g->forks);
}

int	oops_crash(t_all *g, char *error)
{
	free_tabs(g);
	printf("%s\n", error);
	return (EXIT_FAILURE);
}