/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3c_philos_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:15:32 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/19 17:39:10 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  crunch_crunch(t_philo *p)
{
    if (p->died == NO && p->all_meals_done == NO)
    {    
        pthread_mutex_lock(p->fork);
        printf("%zu philo %zu has taken a fork\n", get_now(p->time_start), p->i_am);
        if (!p->nxt_fork)
            return (ERROR);
        pthread_mutex_lock(p->nxt_fork);
        printf("%zu philo %zu has taken a fork\n", get_now(p->time_start), p->i_am);
        printf("%zu philo %zu is eating\n", get_now(p->time_start), p->i_am);
        p->time_last_meal = get_now(p->time_start);
        p->eaten++;
        usleep(p->time_eat * 1000);
        pthread_mutex_unlock(p->fork);
        pthread_mutex_unlock(p->nxt_fork);
    }
    return (EXIT_SUCCESS);
}

void    *eat_sleep_think(void *philo)
{
    t_philo  *p;

    p = (t_philo *)philo;
    if (!p)
        return (NULL);
    if (p->i_am % 2 == 0)
        usleep(100);
    while (1)
    {
        if (crunch_crunch(p) == ERROR)
            return (NULL);
        if (p->nb_meals > 0 && p->eaten == p->nb_meals)
        {
            p->all_meals_done = YES;
            return (NULL);
        }
        printf("%zu philo %zu is sleeping\n", get_now(p->time_start), p->i_am);
        usleep(p->time_sleep * 1000);
        printf("%zu philo %zu is thinking\n", get_now(p->time_start), p->i_am);
    }
    return (NULL);
}
