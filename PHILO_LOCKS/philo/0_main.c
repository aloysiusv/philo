/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:11 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/31 21:42:56 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	exit_simulation(t_all *god)
{
	size_t	i;

	i = 0;
	while (i < god->nb_philo)
		if (pthread_join(god->philos[i++].thread, NULL) != 0)
			return (printf("Detaching failed\n"), ERROR);
	if (pthread_join(god->god_thread, NULL) != 0)
		return (printf("Joining god failed\n"), ERROR);
	i = 0;
	while (i < god->nb_philo)
		pthread_mutex_destroy(&god->philos[i++].fork);
	pthread_mutex_destroy(&god->writing);
	pthread_mutex_destroy(&god->check_death);
	pthread_mutex_destroy(&god->check_meals);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_all	god;

	memset(&god, 0, sizeof(t_all));
	if (check_args(argc, argv) == ERROR)
		return (oops_crash(&god, "error: philo: invalid arguments"));
	if (initialising(&god, argv) == ERROR)
		return (oops_crash(&god, "error: philo: init failed"));
	if (launch_simulation(&god) == ERROR)
		return (oops_crash(&god, "error: philo: launching failed"));
	if (exit_simulation(&god) == ERROR)
		return (oops_crash(&god, "error: philo: exit failed"));
	free_tabs(&god);
	return (EXIT_SUCCESS);
}
