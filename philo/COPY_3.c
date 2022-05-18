/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   COPY_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:19:47 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/15 05:05:01 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_fork()
{
    
}

static void *eat_forever(void *philo)
{
    t_philo   *p;

    p = (t_philo *)philo;
    while (1)
    {
        pthread_mutex_lock(p->fork);
        printf("%zu philo %zu has taken a fork\n",
            return_timestamp(p->milli_start), p->i_am);
        pthread_mutex_lock(p->nxt_fork);
        printf("%zu philo %zu has taken next fork\n",
            return_timestamp(p->milli_start), p->i_am);
        printf("%zu philo %zu is eating\n",
            return_timestamp(p->milli_start), p->i_am);
        usleep(p->milli_eat * 1000);
        pthread_mutex_unlock(p->fork);
        pthread_mutex_unlock(p->nxt_fork);
        printf("%zu philo %zu is sleeping\n",
            return_timestamp(p->milli_start), p->i_am);
        usleep(p->milli_sleep * 1000);
        printf("%zu philo %zu is thinking\n",
            return_timestamp(p->milli_start), p->i_am);
    }
    return (EXIT_SUCCESS);
}

static void    *all_you_can_eat(void *all)
{
    size_t  i;
    t_all   *t;
    
    t = (t_all *)all; 
    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_create(&t->phi_threads[i], NULL, &eat_forever,
            &t->phi_structs[i]) != 0)
            return (ERROR);
        i++;
    }
    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_join(t->phi_threads[i], NULL) != 0)
            return (ERROR);
        i++;
    }
    return (EXIT_SUCCESS);
}

static void    *not_all_you_can_eat(void *all)
{
    size_t  i;
    t_all   *t;
    
    t = (t_all *)all; 
    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_create(&t->phi_threads[i], NULL, &eat_till_enough,
            &t->phi_structs[i]) != 0)
            return (ERROR);
        i++;
    }
    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_join(t->phi_threads[i], NULL) != 0)
            return (ERROR);
        i++;
    }
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

int    awake_god_almighty(t_all *t)
{
    size_t      i;
    size_t      start;
    pthread_t   god;
    
    start = get_starting_time();
    i = 0;
    while (i++ < t->nb_philo)
    {
        pthread_mutex_init(&t->all_forks[i], NULL);
        t->phi_structs[i].i_am = i + 1;
        t->phi_structs[i].fork = &t->all_forks[i];
        t->phi_structs[i].nxt_fork = &t->all_forks[(i + 1) % t->nb_philo];
        t->phi_structs[i].eaten = 0;
        t->phi_structs[i].died = 0;
        t->phi_structs[i].milli_start = start;
    }
    if (&t->phi_structs[0].nb_meals == 0)
        if (pthread_create(&god, NULL, &all_you_can_eat, &t) != 0)
            return (ERROR);
    else
        if (pthread_create(&god, NULL, &not_all_you_can_eat, &t) != 0)
            return (ERROR);
    i = 0;
    if (pthread_join(god, NULL) != 0)
        return (ERROR);
    while (i < t->nb_philo)
        pthread_mutex_destroy(&t->all_forks[i++]);
}
