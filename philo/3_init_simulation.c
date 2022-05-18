/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:19:47 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/15 04:32:42 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t   return_timestamp(size_t milli_start)
{
    struct timeval    tv;
    size_t            milli_now;
    int               ret;

    ret = gettimeofday(&tv, NULL);
    if (ret == -1)
        return (EXIT_FAILURE);
    milli_now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (milli_now - milli_start);
}

static void *eat_sleep_think(void *philo)
{
    t_philo   *p;

    p = (t_philo *)philo;
    while (1)
    {
        pthread_mutex_lock(p->fork);
        printf("%zu philo %zu has taken a fork\n", return_timestamp(p->milli_start),
            p->i_am);
        
        pthread_mutex_lock(p->nxt_fork);
        printf("%zu philo %zu has taken next fork\n", return_timestamp(p->milli_start), p->i_am);
        printf("%zu philo %zu is eating\n", return_timestamp(p->milli_start), p->i_am);
        usleep(p->milli_eat * 1000);
        pthread_mutex_unlock(p->fork);
        pthread_mutex_unlock(p->nxt_fork);
        printf("%zu philo %zu is sleeping\n", return_timestamp(p->milli_start), p->i_am);
        usleep(p->milli_sleep * 1000);
        printf("%zu philo %zu is thinking\n", return_timestamp(p->milli_start), p->i_am);

    }
    return (EXIT_SUCCESS);
}

static void *monitoring(void *all)
{
    t_all   *t;

    t = (t_all *)all;
    
}

static int  launch_god_thread(t_all *t)
{
    size_t      i;
    pthread_t   god;

    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_create(&t->phi_threads[i], NULL, &eat_sleep_think,
            &t->phi_structs[i]) != 0)
            return (ERROR);
        i++;
    }
    pthread_create(&god, NULL, &monitoring, t);
    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_join(t->phi_threads[i], NULL) != 0)
            return (ERROR);
        i++;
    }
    pthread_join(&god, NULL);
    return (EXIT_SUCCESS);
}

static size_t   get_starting_time()
{
    struct timeval    tv;
    size_t            start;
    int               ret;

    ret = gettimeofday(&tv, NULL);
    if (ret == ERROR)
        return (EXIT_FAILURE);
    start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (start);
}

int    init_simulation(t_all *t)
{
    size_t  i;
    size_t  start;

    start = get_starting_time();
    i = 0;
    while (i < t->nb_philo)
    {
        pthread_mutex_init(&t->all_forks[i], NULL);
        t->phi_structs[i].i_am = i + 1;
        t->phi_structs[i].fork = &t->all_forks[i];
        t->phi_structs[i].nxt_fork = &t->all_forks[(i + 1) % t->nb_philo];
        t->phi_structs[i].eaten = 0;
        t->phi_structs[i].died = 0;
        t->phi_structs[i].milli_start = start;
        i++;
    }
    if (launch_god_thread(t) == ERROR)
        return (ERROR);
    i = 0;
    while (i < t->nb_philo)
        pthread_mutex_destroy(&t->all_forks[i++]);
    return (EXIT_SUCCESS);
}
