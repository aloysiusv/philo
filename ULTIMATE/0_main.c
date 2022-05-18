/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:11 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/18 03:35:57 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void set_to_zero(t_philo *t, char *argv[])
{
   size_t   i;

   i = 0;
   while (i < (size_t)ft_atoi(argv[1]))
   {
        t[i].i_am = 0;
        t[i].nb_philo = 0;
        t[i].time_die = 0;
        t[i].time_eat = 0;
        t[i].time_sleep = 0;
        t[i].nb_meals = 0;
        t[i].all_meals_done = 0;
        t[i].time_start = 0;
        t[i].time_last_meal = 0;
        t[i].eaten = 0;
        t[i].died = 0;
        t[i].my_thread = 0;
        t[i].fork = NULL;
        t[i].nxt_fork = NULL;
        i++;
   }
}

int main(int argc, char *argv[])
{
    t_philo   *t;

    if (check_args(argc, argv) == ERROR)
        return (oops_crash(NULL, "error: philo: invalid arguments"));
    t = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
    if (!t)
        return (oops_crash(t, "error: philo: 'malloc' failed"));
    set_to_zero(t, argv);
    if (initialising(t, argv) == ERROR)
        return (oops_crash(t, "error: philo: init failed"));
    if (launch_simulation(t) == ERROR)
        return (oops_crash(t, "error: philo: couldn't launch simulation"));
    free_all(t);
    return (EXIT_SUCCESS);
}
