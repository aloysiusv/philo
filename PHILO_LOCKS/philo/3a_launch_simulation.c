/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3a_launch_simulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:16:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/31 21:33:25 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*god_routine(void *god)
{
	t_all	*g;

	g = (t_all *)god;
	if (!g)
		return (NULL);
	while (1)
	{
		if (did_someone_die(god) == YES)
			return (NULL);
		if (did_everyone_eat(god) == YES)
			return (NULL);
	}
	return (NULL);
}

void	*philosophize(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	if (!p)
		return (NULL);
	while (1)
		if (eat_sleep_think(p) == ERROR)
			return (NULL);
	return (NULL);
}

int	launch_simulation(t_all *g)
{
	size_t		i;

	i = 0;
	while (i < g->nb_philo)
	{
		if (pthread_create(&g->philos[i].thread, NULL,
			&philosophize, &g->philos[i]) != 0)
			return (printf("Failed to create PHILO %zu", i), ERROR);
		i++;
	}
	if (pthread_create(&g->god_thread, NULL, &god_routine, g) != 0)
		return (printf("Failed to create GOD\n"), ERROR);
	return (EXIT_SUCCESS);
}
