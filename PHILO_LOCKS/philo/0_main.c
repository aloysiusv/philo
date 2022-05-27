/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:11 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/27 19:52:57 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_all			god;
	pthread_mutex_t	big_lock;

	if (check_args(argc, argv) == ERROR)
		return (oops_crash(NULL, "error: philo: invalid arguments"));
	memset(&god, 0, sizeof(t_all));
	pthread_mutex_init(&big_lock, NULL);
	pthread_mutex_lock(&big_lock);
	if (initialising(&god, argv) == ERROR)
		return (oops_crash(&god, "error: philo: init failed"));
	if (launch_simulation(&god) == ERROR)
		return (oops_crash(&god, "error: philo: couldn't launch simulation"));
	pthread_mutex_unlock(&big_lock);
	pthread_mutex_destroy(&big_lock);
	free_tabs(&god);
	return (EXIT_SUCCESS);
}
