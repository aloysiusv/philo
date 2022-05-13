/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:19:47 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/13 21:59:59 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *eat_sleep_think(t_philo philo)
{
    
}

void    init_simulation(t_all *t)
{
    size_t  i;

    i = -1;
    while (++i < t->nb_philo)
    {
        pthread_mutex_init(&t->all_forks[i], NULL);
        t->phi_structs[i].i_am = i + 1;
        t->phi_structs[i].fork = &t->all_forks[i];
        t->phi_structs[i].nxt_fork = &t->all_forks[i % t->nb_philo];
        t->phi_structs[i].eaten = 0;
        t->phi_structs[i].died = 0;
    }
    i = -1;
    while (++i < t->nb_philo)
    {
        pthread_create(&t->phi_threads[i], NULL,
            &eat_sleep_think, &t->phi_structs[i]);
    }
    i = -1;
    while (++i < t->nb_philo)
        pthread_join(&t->phi_threads[i], NULL);
}