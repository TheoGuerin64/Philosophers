/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:08:17 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/25 21:09:07 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checking_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo))
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	*is_hungry_philo_routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	i = 0;
	while (i < philos->infos->philo_nb)
	{
		sem_wait(philos->shared->sem_eat);
		i++;
	}
	sem_post(philos->shared->sem_stop);
	return (NULL);
}
