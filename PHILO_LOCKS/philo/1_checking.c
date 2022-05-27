/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_checking.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:02:37 by lrandria          #+#    #+#             */
/*   Updated: 2022/05/27 01:52:20 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	is_str_int_sized(char *str)
{
	while (*str == '0')
		str++;
	if (ft_strlen(str) > 10)
		return (ERROR);
	return (0);
}

static int	is_str_only_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[0] == '0' && ft_strlen(str) == 1) || ft_isdigit(str[i]) == 0)
			return (ERROR);
		i++;
	}
	return (0);
}

int	check_args(int argc, char *argv[])
{
	size_t	i;

	if (argc < 5 || argc > 6)
		return (ERROR);
	i = 1;
	while (argv[i])
	{
		if (is_str_only_digits(argv[i]) == ERROR)
			return (ERROR);
		if (is_str_int_sized(argv[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (0);
}
