/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:36:27 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 18:52:51 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NO_COLOR 0
# define BLUE "\e[38;5;39m"
# define GREEN "\e[38;5;28m"
# define RED "\e[38;5;196m"
# define YELLOW "\e[38;5;82m"
# define GREY "\e[38;5;245m"
# define RESET "\e[0m"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef enum e_state
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}		t_state;

typedef struct s_infos
{
	int		philo_nb;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_must_eat;
	long	start_time;
}		t_infos;

typedef struct s_shared
{
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_time_last_eat;
	pthread_mutex_t	mutex_nb_eat;
}		t_shared;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	t_state		state;
	int			eat_nb;
	int			time_last_eat;
	t_infos		*infos;
	t_shared	*shared;
}		t_philo;

// ------------------------ PARSING ------------------------ //

int			parse_infos(t_infos *infos, char **strings, int size);

// ------------------------ PHILOS ------------------------ //

t_philo		*create_philos(t_infos *infos, t_shared *shared);
void		*philo_routine(void *arg);
void		print_state(t_philo *philo, t_state state);
int			is_hungry_philo(t_infos *infos, t_shared *shared, t_philo *philos);
int			is_dead_philo(t_infos *infos, t_shared *shared, t_philo *philos);
int			is_stopped(t_shared *shared);
void		update_time_last_eat(t_philo *philo);

// ------------------------ THREADS ------------------------ //

int			create_threads(t_infos *infos, t_philo *philos);
void		wait_threads(t_philo *philos, int thread_nb);

// ------------------------ UTILS ------------------------ //

int			ft_atoi(const char *nptr, int *error_flag);
long		timestamp_ms(void);
long		elapsed_time(t_infos *infos);
char		*ft_strcpy(char *dest, const char *src);

#endif
