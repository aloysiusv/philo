/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_initialising.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:09:33 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/18 00:58:07 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t   get_start_time()
{
    struct timeval    tv;
    size_t            start;
    int               ret;

    ret = gettimeofday(&tv, NULL);
    if (ret == ERROR)
        return (0);
    start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (start);
}

static int  free_forks(t_philo *t, size_t till_here)
{
    size_t	i;

	i = 0;
	while (i < till_here)
		free(t[i++].fork);
    return (ERROR);
}

static int  init_forks(t_philo *t)
{
    size_t  i;
    size_t  all_philos;

    all_philos = t[0].nb_philo;
    i = 0;
    while (i < all_philos)
    {
        t[i].fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        if (!t[i].fork)
            return (free_forks(t, i));
        pthread_mutex_init(t[i++].fork, NULL);
    }
    if (all_philos == 1)
        return (EXIT_SUCCESS);
    i = 0;
    while (i < all_philos)
    {
        t[i].nxt_fork = t[(i + 1) % all_philos].fork;
        i++;
    }
    return (EXIT_SUCCESS);
}

int initialising(t_philo *t, char *argv[])
{
    size_t      i;
    size_t      start;
    size_t      num;

    start = get_start_time();
    if (!start)
        return (ERROR);
    i = 0;
    num = ft_atoi(argv[1]);
    while (i < num)
    {
        t[i].i_am = i + 1;
        t[i].nb_philo = num;
        t[i].time_die = ft_atoi(argv[2]);
        t[i].time_eat = ft_atoi(argv[3]);
        t[i].time_sleep = ft_atoi(argv[4]);
        if (argv[5])
            t[i].nb_meals = ft_atoi(argv[5]);
        t[i++].time_start = start;
    }
    if (init_forks(t) == ERROR)
        return (ERROR);
    return (EXIT_SUCCESS);
}