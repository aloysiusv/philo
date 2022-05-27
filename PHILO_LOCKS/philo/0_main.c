/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:11 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/27 01:30:32 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_all	god;

	if (check_args(argc, argv) == ERROR)
		return (oops_crash(NULL, "error: philo: invalid arguments"));
	memset(&god, 0, sizeof(t_all));
	if (initialising(&god, argv) == ERROR)
		return (oops_crash(&god, "error: philo: init failed"));
	if (launch_simulation(&god) == ERROR)
		return (oops_crash(&god, "error: philo: couldn't launch simulation"));
	free_mutex_mallocs(&god);
	return (EXIT_SUCCESS);
}
