/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:15:26 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/27 02:22:04 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h> 
# include <limits.h>
# include <string.h>
# include <pthread.h>

# define ERROR	-1
# define NO		0
# define YES	1

typedef struct s_philo
{
	size_t		i_am;
	size_t		eaten;
	size_t		all_meals_done;
	long int	time_last_meal;
	size_t		fork;
	size_t		nxt_fork;
	t_all		*god;
}				t_philo;

typedef struct s_all
{
	size_t				nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	size_t				nb_meals;
	int					one_died;
	long int			time_start;
	t_philo				*philos;
	pthread_mutex_t		*writing;
	pthread_mutex_t		*forks;
}						t_all;

int		check_args(int argc, char *argv[]);
int		initialising(t_all *g, char *argv[]);
int		launch_simulation(t_all *g);

size_t	get_timestamp(size_t milli_start);
void	*god_routine(void *everyone);
void	*eat_sleep_think(void *philo);

int		oops_crash(t_all *g, char *error);
void	free_all(t_all *g);

#endif // PHILO_H
