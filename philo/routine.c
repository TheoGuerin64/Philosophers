/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:08:17 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/12 20:47:06 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_forks_back(t_philo *philo)
{
	pthread_mutex_unlock(philo->shared->forks + philo->id - 1);
	pthread_mutex_unlock(philo->shared->forks
		+ philo->id % philo->infos->philo_nb);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->shared->forks + philo->id - 1);
	print_state(philo, TAKE_FORK);
	pthread_mutex_lock(philo->shared->forks
		+ philo->id % philo->infos->philo_nb);
	print_state(philo, TAKE_FORK);
}

static int	philo_eat(t_philo *philo)
{
	take_forks(philo);
	update_time_last_eat(philo);
	print_state(philo, EAT);
	usleep(philo->infos->time_eat * 1000);
	put_forks_back(philo);
	if (philo->infos->nb_must_eat != -1)
	{
		pthread_mutex_lock(&philo->shared->mutex_nb_eat);
		philo->eat_nb += 1;
		pthread_mutex_unlock(&philo->shared->mutex_nb_eat);
	}
	return (1);
}

static void	routine_loop(t_philo *philo)
{
	while (!is_stopped(philo->shared))
	{
		if (philo->state == EAT)
		{
			if (philo->infos->philo_nb == 1)
			{
				print_state(philo, TAKE_FORK);
				usleep(philo->infos->time_die);
				return ;
			}
			philo_eat(philo);
			philo->state = SLEEP;
		}
		else if (philo->state == SLEEP)
		{
			print_state(philo, SLEEP);
			usleep(philo->infos->time_sleep * 1000);
			philo->state = THINK;
		}
		else if (philo->state == THINK)
		{
			print_state(philo, THINK);
			philo->state = EAT;
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(5000);
	philo->state = EAT;
	routine_loop(philo);
	return (NULL);
}
