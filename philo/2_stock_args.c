/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_stock_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 01:33:48 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/15 01:47:32 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int malloc_all_tabs(t_all *t)
{
    t->all_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
            t->nb_philo);
    if (!t->all_forks)
        return (ERROR);
    t->phi_threads = (pthread_t *)malloc(sizeof(pthread_t) * t->nb_philo);
    if (!t->phi_threads)
    {
        free(t->all_forks);
        return (ERROR);
    }
    t->phi_structs = (t_philo *)malloc(sizeof(t_philo) * t->nb_philo);
    if (!t->phi_structs)
    {
        free(t->all_forks);
        free(t->phi_threads);
        return (ERROR);
    }
    return (EXIT_SUCCESS);
}

static void set_to_zero(t_philo *philo)
{
    philo->i_am = 0;
    philo->milli_die = 0;
    philo->milli_eat = 0;
    philo->milli_sleep = 0;
    philo->milli_start = 0;
    philo->milli_last_meal = 0;
    philo->nb_meals = 0;
    philo->eaten = 0;
    philo->fork = NULL;
    philo->nxt_fork = NULL;
    philo->died = 0;
}

int  stock_args(t_all *t, char *argv[])
{
    size_t  i;

    t->nb_philo = ft_atoi(argv[1]);
    if (malloc_all_tabs(t) == ERROR)
    {
        printf("error: philo: 'malloc' failed\n");
        return (ERROR);
    }
    i = 0;
    while (i < t->nb_philo)
    {
        set_to_zero(&t->phi_structs[i]);
        t->phi_structs[i].milli_die = ft_atoi(argv[2]);
        t->phi_structs[i].milli_eat = ft_atoi(argv[3]);
        t->phi_structs[i].milli_sleep = ft_atoi(argv[4]);
        if (argv[5])
            t->phi_structs[i].nb_meals = ft_atoi(argv[5]);
        i++;
    }
    return (EXIT_SUCCESS);
}
