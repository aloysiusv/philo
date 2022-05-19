/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_launch_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:16:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/19 09:52:44 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t   get_timestamp(size_t milli_start)
{
    struct timeval    tv;
    size_t            milli_now;
    
    gettimeofday(&tv, NULL);
    milli_now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (milli_now - milli_start);
}

static int did_everyone_eat(t_philo *t)
{
    size_t  i;
    size_t  meals;
    size_t  count;

    i = 0;
    meals = t[0].nb_meals;
    count = 0;
    while (i < t[0].nb_philo)
    {
        if (t[i].all_meals_done)
            count++;
        if (count == meals)
            return (YES);
        i++;
    }
    return (NO);
}

static int  is_dinner_over(t_philo *p)
{
    size_t  i;
    size_t  since_last_meal;

    i = 0;
    while (i < p[0].nb_philo)
    {
        since_last_meal =
            get_timestamp(p[0].time_start) - p[i].time_last_meal;
        if (since_last_meal > p[0].time_die)
        {
            p[i].died = YES;
            return (YES);
        }
        if (did_everyone_eat(p) == YES)
            return (YES);
        i++;
    }
    return (EXIT_SUCCESS);
}


static void *eat_sleep_think(void *philo)
{
    t_philo  *p;

    p = (t_philo *)philo;
    while (1)
    {
        pthread_mutex_lock(p->fork);
        printf("%zu philo %zu has taken a fork\n",
            get_timestamp(p->time_start), p->i_am);
        if (!p->nxt_fork)
            return (NULL);
        pthread_mutex_lock(p->nxt_fork);
        printf("%zu philo %zu has taken a fork\n",
            get_timestamp(p->time_start), p->i_am);
        printf("%zu philo %zu is eating\n",
            get_timestamp(p->time_start), p->i_am);
        usleep(p->time_eat * 1000);
        p->eaten++;
        p->time_last_meal = get_timestamp(p->time_start);
        pthread_mutex_unlock(p->fork);
        pthread_mutex_unlock(p->nxt_fork);
        if (p->nb_meals > 0 && p->eaten >= p->nb_meals)
        {
            p->all_meals_done = YES;
            return (NULL);
        }
        printf("%zu philo %zu is sleeping\n",
            get_timestamp(p->time_start), p->i_am);
        usleep(p->time_sleep * 1000);
        printf("%zu philo %zu is thinking\n",
            get_timestamp(p->time_start), p->i_am);
    }
    return (NULL);
}

static void *god_routine(void *everyone)
{
    size_t  i;
    t_philo *philos;

    i = 0;
    philos = (t_philo *)everyone;
    while (i < philos[0].nb_philo)
    {
        if (is_dinner_over(philos) == YES)
        {
            if (philos[i].died)
            {
                printf("%zu philo %zu died\n",
                    get_timestamp(philos[i].time_start), philos[i].i_am);
                return (NULL);
            }
            else
                return (printf("Tout le monde a graillé\n"), NULL);
        }
        i++;
        if (i == philos[0].nb_philo)
            i = 0;
    }
    return (NULL);
}

int    launch_simulation(t_philo *t)
{
    size_t      i;
    pthread_t   god;

    i = 0;
    if (pthread_create(&god, NULL, &god_routine, t) != 0)
        return (ERROR);
    while (i < t->nb_philo)
    {
        if (pthread_create(&t[i].my_thread, NULL, &eat_sleep_think, &t[i]) != 0)
            return (ERROR);
        i++;
    }
    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_detach(t[i].my_thread) != 0)
            return (ERROR);
        i++;
    }
    i = 0;
    while (i < t->nb_philo)
    {
        pthread_mutex_destroy(t[i].fork);
        i++;
    }
    if (pthread_join(god, NULL) != 0)
        return (ERROR);
    return (EXIT_SUCCESS);
}
