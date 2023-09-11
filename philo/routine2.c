/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:42:44 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/12 20:46:41 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_time_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->mutex_time_last_eat);
	philo->time_last_eat = elapsed_time(philo->infos);
	pthread_mutex_unlock(&philo->shared->mutex_time_last_eat);
}

int	is_stopped(t_shared *shared)
{
	int	result;

	pthread_mutex_lock(&shared->mutex_stop);
	result = shared->stop;
	pthread_mutex_unlock(&shared->mutex_stop);
	return (result);
}
