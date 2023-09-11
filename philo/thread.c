/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:14:51 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/16 15:22:11 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_philo *philos, int thread_nb)
{
	int		i;

	i = 0;
	while (i < thread_nb)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	create_threads(t_infos *infos, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < infos->philo_nb)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, philos + i))
		{
			write(2, "philo: Error while creating threads\n", 36);
			wait_threads(philos, i);
			return (0);
		}
		i++;
	}
	return (1);
}
