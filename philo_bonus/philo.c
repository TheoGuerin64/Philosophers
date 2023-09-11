/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:11:47 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 17:21:27 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	time_last_eat;

	sem_wait(philo->shared->sem_time_last_eat);
	time_last_eat = philo->time_last_eat;
	sem_post(philo->shared->sem_time_last_eat);
	if (elapsed_time(philo->infos) - time_last_eat >= philo->infos->time_die)
	{
		print_state(philo, DEAD);
		sem_post(philo->shared->sem_stop);
		return (1);
	}
	return (0);
}

void	check_hunger(t_philo *philo)
{
	if (philo->eat_nb == philo->infos->nb_must_eat)
		sem_post(philo->shared->sem_eat);
}

t_philo	*create_philos(t_infos *infos, t_shared *shared)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(*philos) * infos->philo_nb);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < infos->philo_nb)
	{
		philos[i].id = i + 1;
		philos[i].infos = infos;
		philos[i].shared = shared;
		philos[i].eat_nb = 0;
		philos[i].time_last_eat = 0;
		i++;
	}
	return (philos);
}
