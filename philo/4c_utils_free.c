/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4c_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:56:56 by lrandria          #+#    #+#             */
/*   Updated: 2022/06/03 06:26:10 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_tabs(t_all *g)
{
	if (g->philos)
		free(g->philos);
}

int	oops_crash(t_all *g, char *error)
{
	free_tabs(g);
	printf("%s\n", error);
	return (ERROR);
}
