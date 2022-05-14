/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:11 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/14 02:49:51 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int malloc_all_tabs(t_all *t)
{
    t->all_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * t->nb_philo);
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

static void free_all_tabs(t_all *t)
{
    free(t->all_forks);
    free(t->phi_threads);
    free(t->phi_structs);
}

static size_t   get_starting_time()
{
    struct timeval    tv;
    size_t            my_start;
    int               ret;

    ret = gettimeofday(&tv, NULL);
    if (ret == ERROR)
        return (EXIT_FAILURE);
    my_start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (my_start);
}

static int  init_info(t_all *t, char *argv[])
{
    size_t  i;
    size_t  start;

    t->nb_philo = ft_atoi(argv[1]);
    if (malloc_all_tabs(t) == ERROR)
    {
        printf("error: philo: 'malloc' failed\n");
        return (ERROR);
    }
    i = 0;
    start = get_starting_time();
    while (i < t->nb_philo)
    {
        t->phi_structs[i].milli_die = ft_atoi(argv[2]);
        t->phi_structs[i].milli_eat = ft_atoi(argv[3]);
        t->phi_structs[i].milli_sleep = ft_atoi(argv[4]);
        if (argv[5])
            t->phi_structs[i].nb_meals = ft_atoi(argv[5]);
        t->phi_structs[i].milli_start = start;
        i++;
    }
    return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    t_all   t[1];

    if (check_args(argc, argv) == ERROR)
    {
        printf("error: philo: invalid arguments\n");
        return (EXIT_FAILURE);
    }
    if (init_info(t, argv) == ERROR)
        return (EXIT_FAILURE);
    if (init_simulation(t) == ERROR)
    {
        free_all_tabs(t);
        return (EXIT_FAILURE);
    }
    // launch_simulation(t);
    // exit_simulation(t);
    free_all_tabs(t);
    return (EXIT_SUCCESS);
}
