/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:55:42 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/05 18:38:09 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_shared(t_infos *infos, t_shared *shared)
{
	int	i;

	shared->forks = malloc(sizeof(*shared->forks) * infos->philo_nb);
	if (!shared->forks)
		return (0);
	shared->stop = 0;
	i = 0;
	while (i < infos->philo_nb)
	{
		pthread_mutex_init(shared->forks + i, NULL);
		i++;
	}
	pthread_mutex_init(&shared->mutex_printf, NULL);
	pthread_mutex_init(&shared->mutex_stop, NULL);
	pthread_mutex_init(&shared->mutex_time_last_eat, NULL);
	pthread_mutex_init(&shared->mutex_nb_eat, NULL);
	return (1);
}

static void	destroy_shared(t_infos *infos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < infos->philo_nb)
	{
		pthread_mutex_destroy(shared->forks + i);
		i++;
	}
	pthread_mutex_destroy(&shared->mutex_printf);
	pthread_mutex_destroy(&shared->mutex_stop);
	pthread_mutex_destroy(&shared->mutex_time_last_eat);
	pthread_mutex_destroy(&shared->mutex_nb_eat);
	free(shared->forks);
}

static void	main_loop(t_infos *infos, t_shared *shared, t_philo *philos)
{
	while (!is_dead_philo(infos, shared, philos)
		&& is_hungry_philo(infos, shared, philos))
		usleep(1000);
	pthread_mutex_lock(&shared->mutex_stop);
	shared->stop = 1;
	pthread_mutex_unlock(&shared->mutex_stop);
}

int	main(int argc, char **argv)
{
	t_shared	shared;
	t_infos		infos;
	t_philo		*philos;

	if (!parse_infos(&infos, argv + 1, argc - 1))
		return (EXIT_FAILURE);
	if (!init_shared(&infos, &shared))
		return (EXIT_FAILURE);
	philos = create_philos(&infos, &shared);
	if (!philos)
	{
		destroy_shared(&infos, &shared);
		return (EXIT_FAILURE);
	}
	infos.start_time = timestamp_ms();
	if (!create_threads(&infos, philos))
	{
		destroy_shared(&infos, &shared);
		free(philos);
		return (EXIT_FAILURE);
	}
	main_loop(&infos, &shared, philos);
	wait_threads(philos, infos.philo_nb);
	destroy_shared(&infos, &shared);
	free(philos);
}
