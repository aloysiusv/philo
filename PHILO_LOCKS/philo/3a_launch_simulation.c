/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_launch_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:16:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/27 19:37:25 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*god_routine(void *god)
{
	t_all	*g;

	g = (t_all *)god;
	if (!g)
		return (NULL);
	// while (1)
	// 	if (did_someone_die(p) == YES || did_everyone_eat(p) == YES)
	// 		return (NULL);
	pthread_mutex_lock(&g->death);
	printf("HELLO FROM GOD\n");
	pthread_mutex_unlock(&g->death);
	return (NULL);
}

void	*philosophize(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	if (!p)
		return (NULL);
	pthread_mutex_lock(&p->god->writing);
	printf("Hello from philo %zu\n", p->i_am);
	pthread_mutex_unlock(&p->god->writing);
	// while (1)
	// {
	// 	if (crunch_crunch(g) == ERROR)
	// 		return (NULL);
	// 	if (g->nb_meals > 0 && g-> == g->nb_meals)
	// 	{
	// 		g->all_meals_done = YES;
	// 		return (NULL);
	// 	}
	// 	if (g->died == NO && g->all_meals_done == NO)
	// 	{
	// 		printf("%zums philo %zu is sleeping\n",
	// 			get_now(g->time_start), g->i_am);
	// 		usleep(g->time_sleep * 1000);
	// 		if (g->died == NO && g->all_meals_done == NO)
	// 			printf("%zums philo %zu is thinking\n",
	// 				get_now(g->time_start), g->i_am);
	// 	}
	// }
	return (NULL);
}

int	launch_simulation(t_all *g)
{
	size_t		i;
	pthread_t	philos;
	pthread_t	god;

	if (pthread_create(&god, NULL, &god_routine, &g))
		return (ERROR);
	i = 0;
	while (i < g->nb_philo)
	{
		if (pthread_create(&philos, NULL, &philosophize, &g->philos[i]) != 0)
			return (ERROR);
		i++;
	}
	i = 0;
	while (i < g->nb_philo)
		if (pthread_join(philos, NULL) != 0)
			return (ERROR);
	if (pthread_join(god, NULL) != 0)
		return (ERROR);
	i = 0;
	while (i < g->nb_philo)
		pthread_mutex_destroy(&g->forks[i++]);
	pthread_mutex_destroy(&g->writing);
	pthread_mutex_destroy(&g->death);
	pthread_mutex_destroy(&g->miam);
	return (EXIT_SUCCESS);
}
