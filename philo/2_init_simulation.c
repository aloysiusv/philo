/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:19:47 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/14 00:07:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *eat_sleep_think(t_philo philo)
{
    
}

static int  launch_threads(t_all *t)
{
    size_t  i;

    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_create(&t->phi_threads[i], NULL, &eat_sleep_think,
            &t->phi_structs[i] != 0))
            return (ERROR);
        i++;
    }
    i = 0;
    while (i < t->nb_philo)
    {
        if (pthread_join(&t->phi_threads[i], NULL) != 0)
            return (ERROR);
        i++;
    }
    return (EXIT_SUCCESS);
}

int    init_simulation(t_all *t)
{
    size_t  i;

    i = 0;
    while (i < t->nb_philo)
    {
        pthread_mutex_init(&t->all_forks[i], NULL);
        t->phi_structs[i].i_am = i + 1;
        t->phi_structs[i].fork = &t->all_forks[i];
        t->phi_structs[i].nxt_fork = &t->all_forks[(i + 1) % t->nb_philo];
        t->phi_structs[i].eaten = 0;
        t->phi_structs[i].died = 0;
        i++;
    }
    if (launch_threads(t) == ERROR)
        return (ERROR);
    i = 0;
    while (i < t->nb_philo)
        pthread_mutex_destroy(&t->all_forks[i++]);
    return (EXIT_SUCCESS);
}
