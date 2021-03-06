/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:15:26 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/03 09:18:45 by lrandria         ###   ########.fr       */
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

# define ERROR			-1
# define NO				0
# define YES			1

# define CURRENT_TIME	0
# define TIMESTAMP		1

typedef struct s_all	t_all;

typedef struct s_philo
{
	size_t				i_am;
	size_t				eaten;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		*nxt_fork;
	long int			time_last_meal;
	t_all				*god;
}				t_philo;

typedef struct s_all
{
	size_t				nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	size_t				nb_meals;
	long int			time_start;
	pthread_t			god_thread;
	size_t				end;
	t_philo				*philos;
	pthread_mutex_t		writing;
	pthread_mutex_t		check_death;
	pthread_mutex_t		check_meals;
}						t_all;

int		check_args(int argc, char *argv[]);
int		initialising(t_all *g, char *argv[]);
int		launch_simulation(t_all *g);

int		did_someone_die(t_all *g);
int		did_everyone_eat(t_all *g);
int		eat_sleep_think(t_philo *p);

int		are_we_done_yet(t_philo *p);
int		ft_print(t_philo *p, char *str);
int		paranoid_usleep(t_all *g, size_t duration);
size_t	get_time(size_t start_time, int option);

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
long	ft_atol(const char *nptr);

int		oops_crash(t_all *g, char *error);
void	free_tabs(t_all *g);
void	free_all(t_all *g);

#endif // PHILO_H
