/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:11 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/24 17:58:32 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*t;
	size_t	i;
	size_t	nb_philos;

	if (check_args(argc, argv) == ERROR)
		return (oops_crash(NULL, "error: philo: invalid arguments"));
	nb_philos = ft_atoi(argv[1]);
	t = (t_philo *)malloc(sizeof(t_philo) * nb_philos);
	if (!t)
		return (oops_crash(t, "error: philo: 'malloc' failed"));
	i = 0;
	while (i < nb_philos)
		memset(&t[i++], 0, sizeof(*t));
	if (initialising(t, argv) == ERROR)
		return (oops_crash(t, "error: philo: init failed"));
	if (launch_simulation(t) == ERROR)
		return (oops_crash(t, "error: philo: couldn't launch simulation"));
	free_all(t);
	return (EXIT_SUCCESS);
}
