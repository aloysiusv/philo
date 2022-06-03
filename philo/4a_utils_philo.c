/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4a_utils_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:26:41 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/03 09:03:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(size_t start_time, int option)
{
	struct timeval	tv;
	size_t			current;

	if (gettimeofday(&tv, NULL) == ERROR)
		return (0);
	current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (option == TIMESTAMP)
		return (current - start_time);
	return (current);
}

int	paranoid_usleep(t_all *god, size_t duration)
{
	size_t	end;

	end = get_time(0, CURRENT_TIME) + duration;
	while (get_time(0, CURRENT_TIME) < end)
	{
		if (are_we_done_yet(&god->philos[0]) == YES)
			return (ERROR);
		usleep(100);
	}
	return (0);
}

int	ft_print(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->god->check_death);
	if (p->god->end == NO)
	{
		pthread_mutex_lock(&p->god->writing);
		printf("%zums philo %zu %s\n",
			get_time(p->god->time_start, TIMESTAMP), p->i_am, str);
		pthread_mutex_unlock(&p->god->writing);
	}
	pthread_mutex_unlock(&p->god->check_death);
	return (EXIT_SUCCESS);
}
