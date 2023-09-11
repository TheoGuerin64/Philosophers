/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:40:32 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 18:52:10 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_vars(t_infos *infos, int *vars[5])
{
	vars[0] = &infos->philo_nb;
	vars[1] = &infos->time_die;
	vars[2] = &infos->time_eat;
	vars[3] = &infos->time_sleep;
	vars[4] = &infos->nb_must_eat;
}

static int	set_value(int *var, char *string)
{
	int	error_flag;

	error_flag = 0;
	*var = ft_atoi(string, &error_flag);
	if (*var < 1 || error_flag == 1)
	{
		write(2, "philo: parsing error\n", 21);
		return (0);
	}
	return (1);
}

static int	set_values(t_infos *infos, char **strings, int size)
{
	int	*vars[5];
	int	i;

	init_vars(infos, vars);
	i = 0;
	while (i < size)
	{
		if (!set_value(vars[i], strings[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_infos(t_infos *infos, char **strings, int size)
{
	if (size != 4 && size != 5)
	{
		write(2, "philo: Wrong number of argument\n", 32);
		return (0);
	}
	infos->nb_must_eat = -1;
	if (!set_values(infos, strings, size))
		return (0);
	return (1);
}
