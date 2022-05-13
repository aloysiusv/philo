/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:15:26 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/13 21:43:07 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h> 
# include <limits.h>
# include <pthread.h>

# define ERROR -1

typedef struct          s_philo
{
    size_t              i_am;
    pthread_mutex_t     *fork;
    pthread_mutex_t     *nxt_fork;
    size_t              eaten;
    int                 died;
}                       t_philo;

typedef struct          s_all
{
    size_t              nb_philo;
    size_t              usec_die;
    size_t              usec_eat;
    size_t              usec_sleep;
    size_t              nb_meals;
    size_t              usec_start;
    t_philo             *phi_structs;
    pthread_t           *phi_threads;
    pthread_mutex_t     *all_forks;
}                       t_all;

int     check_args(int argc, char *argv[]);

size_t	ft_strlen(const char *s);
int     ft_isdigit(int c);
int     ft_atoi(const char *nptr);

#endif // PHILO_H
