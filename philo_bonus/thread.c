/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:14:51 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 16:36:26 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_is_hungry_thread(pthread_t *thread, t_philo *philos)
{
	if (philos->infos->nb_must_eat == -1)
		return (1);
	if (pthread_create(thread, NULL, &is_hungry_philo_routine, philos))
	{
		write(2, "philo: Error while creating threads\n", 36);
		return (0);
	}
	return (1);
}

int	create_death_thread(pthread_t *thread, t_philo *philo)
{
	if (pthread_create(thread, NULL, &death_checking_routine, philo))
	{
		write(2, "philo: Error while creating threads\n", 36);
		return (0);
	}
	return (1);
}
