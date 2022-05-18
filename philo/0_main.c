/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:11 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/15 04:44:52 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_all_tabs(t_all *t)
{
    free(t->all_forks);
    free(t->phi_threads);
    free(t->phi_structs);
}

static void set_to_zero(t_all *t)
{
    t->nb_philo = 0;
    t->all_forks = NULL;
    t->phi_structs = NULL;
    t->phi_threads = NULL;
}

int main(int argc, char *argv[])
{
    t_all       t[1];

    if (check_args(argc, argv) == ERROR)
    {
        printf("error: philo: invalid arguments\n");
        return (EXIT_FAILURE);
    }
    if (stock_args(t, argv) == ERROR)
        return (EXIT_FAILURE);
    if (init_simulation(t) == ERROR)
    {
        free_all_tabs(t);
        return (EXIT_FAILURE);
    }
    free_all_tabs(t);
    return (EXIT_SUCCESS);
}
