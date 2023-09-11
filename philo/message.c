/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:46:46 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/12 20:33:14 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_message(char message[17], t_state state)
{
	if (state == DEAD)
		ft_strcpy(message, "died");
	else if (state == TAKE_FORK)
		ft_strcpy(message, "has taken a fork");
	else if (state == EAT)
		ft_strcpy(message, "is eating");
	else if (state == SLEEP)
		ft_strcpy(message, "is sleeping");
	else if (state == THINK)
		ft_strcpy(message, "is thinking");
}

static void	set_color(char color[12], t_state state)
{
	if (state == DEAD)
		ft_strcpy(color, RED);
	else if (state == TAKE_FORK)
		ft_strcpy(color, YELLOW);
	else if (state == EAT)
		ft_strcpy(color, GREEN);
	else if (state == SLEEP)
		ft_strcpy(color, BLUE);
	else if (state == THINK)
		ft_strcpy(color, GREY);
}

void	print_state(t_philo *philo, t_state state)
{
	char	msg[17];
	char	color[12];

	if (!NO_COLOR)
		set_color(color, state);
	set_message(msg, state);
	pthread_mutex_lock(&philo->shared->mutex_stop);
	if (!philo->shared->stop)
	{
		pthread_mutex_lock(&philo->shared->mutex_printf);
		if (NO_COLOR)
			printf("%ld %d %s\n", elapsed_time(philo->infos), philo->id, msg);
		else
			printf("%s%ld %d %s%s\n", color, elapsed_time(philo->infos),
				philo->id, msg, RESET);
		pthread_mutex_unlock(&philo->shared->mutex_printf);
	}
	pthread_mutex_unlock(&philo->shared->mutex_stop);
}
