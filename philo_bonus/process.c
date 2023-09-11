/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:14:51 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 17:00:11 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_processes(t_philo *philos, int thread_nb)
{
	int		i;

	i = 0;
	while (i < thread_nb)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
}

int	create_processes(t_infos *infos, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < infos->philo_nb)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			write(2, "philo: Error while creating processes\n", 38);
			kill_processes(philos, i);
			return (0);
		}
		else if (philos[i].pid == 0)
		{
			philo_routine(philos + i);
			exit(0);
		}
		i++;
	}
	return (1);
}
