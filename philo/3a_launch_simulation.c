/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_launch_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:16:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/19 17:14:33 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t   get_now(size_t milli_start)
{
    struct timeval    tv;
    size_t            milli_now;
    
    gettimeofday(&tv, NULL);
    milli_now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (milli_now - milli_start);
}

static int join_or_detach(t_philo *t)
{
    size_t  i;

    i = 0;
    if (t->nb_philo >= 80)
    {
        while (i < t->nb_philo)
        {
            if (pthread_join(t[i].my_thread, NULL) != 0)
                return (ERROR);
            i++;
        }
    }
    else
    {
        while (i < t->nb_philo)
        {
            if (pthread_detach(t[i].my_thread) != 0)
                return (ERROR);
            i++;
        }
    }
    return (EXIT_SUCCESS);
}

static int  exit_simulation(t_philo *t, pthread_t *god)
{
    size_t  i;
    
    i = 0;
    if (join_or_detach(t) == ERROR)
        return (ERROR);
    while (i < t->nb_philo)
    {
        pthread_mutex_destroy(t[i].fork);
        i++;
    }
    if (pthread_join(*god, NULL) != 0)
        return (ERROR);
    return (EXIT_SUCCESS);
}    

int launch_simulation(t_philo *t)
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
    if (exit_simulation(t, &god) == ERROR)
        return (ERROR);
    return (EXIT_SUCCESS);
}
