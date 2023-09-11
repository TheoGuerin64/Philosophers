/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:55:42 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 18:46:24 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_shared(t_infos *infos, t_shared *shared)
{
	sem_unlink("forks");
	sem_unlink("stop");
	sem_unlink("printf");
	sem_unlink("priority");
	sem_unlink("time_last_eat");
	shared->sem_forks = sem_open("forks", O_CREAT, 0644, infos->philo_nb);
	shared->sem_stop = sem_open("stop", O_CREAT, 0644, 0);
	shared->sem_printf = sem_open("printf", O_CREAT, 0644, 1);
	shared->sem_priority = sem_open("priority", O_CREAT, 0644, 1);
	shared->sem_time_last_eat = sem_open("time_last_eat", O_CREAT, 0644, 1);
	if (infos->nb_must_eat > 0)
	{
		sem_unlink("eat");
		shared->sem_eat = sem_open("eat", O_CREAT, 0644, 0);
	}
}

static void	destroy_shared(t_infos *infos, t_shared *shared)
{
	sem_close(shared->sem_forks);
	sem_close(shared->sem_stop);
	sem_close(shared->sem_printf);
	sem_close(shared->sem_priority);
	sem_close(shared->sem_time_last_eat);
	if (infos->nb_must_eat > 0)
		sem_close(shared->sem_eat);
}

static int	main_loop(t_infos *infos, t_shared *shared, t_philo *philos)
{
	pthread_t	thread;
	int			i;

	if (!create_is_hungry_thread(&thread, philos))
		return (0);
	sem_wait(shared->sem_stop);
	kill_processes(philos, infos->philo_nb);
	if (infos->nb_must_eat != -1)
	{
		i = 0;
		while (i < infos->philo_nb)
		{
			sem_post(shared->sem_eat);
			i++;
		}
		pthread_join(thread, NULL);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_shared	shared;
	t_infos		infos;
	t_philo		*philos;
	int			return_value;

	if (!parse_infos(&infos, argv + 1, argc - 1))
		return (EXIT_FAILURE);
	init_shared(&infos, &shared);
	philos = create_philos(&infos, &shared);
	if (!philos)
	{
		destroy_shared(&infos, &shared);
		return (EXIT_FAILURE);
	}
	infos.start_time = timestamp_ms();
	return_value = EXIT_SUCCESS;
	if (!create_processes(&infos, philos)
		|| !main_loop(&infos, &shared, philos))
		return_value = EXIT_FAILURE;
	destroy_shared(&infos, &shared);
	free(philos);
	return (return_value);
}
