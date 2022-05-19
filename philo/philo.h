/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:15:26 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/18 03:42:57 by lrandria         ###   ########.fr       */
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
# define NO     0
# define YES    1

typedef struct          s_philo
{
    size_t              i_am;
    size_t              nb_philo;
    size_t              time_die;
    size_t              time_eat;
    size_t              time_sleep;
    size_t              nb_meals;
    size_t              all_meals_done;
    long int            time_start;
    long int            time_last_meal;
    size_t              eaten;
    int                 died;
    pthread_t           my_thread;
    pthread_mutex_t     *fork;
    pthread_mutex_t     *nxt_fork;
}                       t_philo;

int     check_args(int argc, char *argv[]);
int     initialising(t_philo *t, char *argv[]);
int     launch_simulation(t_philo *t);

size_t	ft_strlen(const char *s);
int     ft_isdigit(int c);
int     ft_atoi(const char *nptr);
int     oops_crash(t_philo *t, char *error);
void	free_all(t_philo *t);

#endif // PHILO_H
