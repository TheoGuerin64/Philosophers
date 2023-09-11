/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:08:17 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 17:21:21 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_forks_back(t_philo *philo)
{
	sem_post(philo->shared->sem_forks);
	sem_post(philo->shared->sem_forks);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->shared->sem_priority);
	sem_wait(philo->shared->sem_forks);
	print_state(philo, TAKE_FORK);
	sem_wait(philo->shared->sem_forks);
	print_state(philo, TAKE_FORK);
	sem_post(philo->shared->sem_priority);
}

static void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	sem_wait(philo->shared->sem_time_last_eat);
	philo->time_last_eat = elapsed_time(philo->infos);
	sem_post(philo->shared->sem_time_last_eat);
	print_state(philo, EAT);
	usleep(philo->infos->time_eat * 1000);
	put_forks_back(philo);
	if (philo->infos->nb_must_eat != -1)
	{
		philo->eat_nb += 1;
		check_hunger(philo);
	}
}

static void	routine_loop(t_philo *philo)
{
	while (1)
	{
		if (philo->state == EAT)
		{
			if (philo->infos->philo_nb == 1)
			{
				print_state(philo, TAKE_FORK);
				usleep(philo->infos->time_die * 1000);
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
	pthread_t		thread;
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (!create_death_thread(&thread, philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(5000);
	philo->state = EAT;
	routine_loop(philo);
	return (NULL);
}
