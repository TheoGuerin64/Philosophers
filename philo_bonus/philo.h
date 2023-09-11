/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:36:27 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 18:50:48 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define BLUE "\e[38;5;39m"
# define GREEN "\e[38;5;28m"
# define RED "\e[38;5;196m"
# define YELLOW "\e[38;5;82m"
# define GREY "\e[38;5;245m"
# define RESET "\e[0m"

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
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
	sem_t	*sem_forks;
	sem_t	*sem_stop;
	sem_t	*sem_eat;
	sem_t	*sem_printf;
	sem_t	*sem_priority;
	sem_t	*sem_time_last_eat;
}		t_shared;

typedef struct s_philo
{
	pid_t		pid;
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
void		check_hunger(t_philo *philo);
int			check_death(t_philo *philo);
void		*is_hungry_philo_routine(void *arg);
void		*death_checking_routine(void *arg);

// ------------------------ PROCESSES ------------------------ //

int			create_processes(t_infos *infos, t_philo *philos);
void		kill_processes(t_philo *philos, int thread_nb);

// ------------------------ THREADS ------------------------ //

int			create_is_hungry_thread(pthread_t *thread, t_philo *philos);
int			create_death_thread(pthread_t *thread, t_philo *philos);

// ------------------------ UTILS ------------------------ //

int			ft_atoi(const char *nptr, int *error_flag);
long		timestamp_ms(void);
long		elapsed_time(t_infos *infos);
char		*ft_strcpy(char *dest, const char *src);

#endif
