/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:11:47 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/16 16:30:26 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_philo(t_infos *infos, t_shared *shared, t_philo *philos)
{
	int		is_dead;
	int		i;

	is_dead = 0;
	i = 0;
	pthread_mutex_lock(&shared->mutex_time_last_eat);
	while (i < infos->philo_nb)
	{
		if (elapsed_time(infos) - philos[i].time_last_eat >= infos->time_die)
		{
			is_dead = 1;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&shared->mutex_time_last_eat);
	if (is_dead)
		print_state(philos + i, DEAD);
	return (is_dead);
}

int	is_hungry_philo(t_infos *infos, t_shared *shared, t_philo *philos)
{
	int	is_hungry;
	int	i;

	if (infos->nb_must_eat == -1)
		return (1);
	is_hungry = 0;
	i = 0;
	pthread_mutex_lock(&shared->mutex_nb_eat);
	while (i < infos->philo_nb)
	{
		if (philos[i].eat_nb < infos->nb_must_eat)
		{
			is_hungry = 1;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&shared->mutex_nb_eat);
	return (is_hungry);
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
