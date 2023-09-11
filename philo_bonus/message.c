/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:46:46 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 16:24:40 by tguerin          ###   ########.fr       */
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

	set_color(color, state);
	set_message(msg, state);
	sem_wait(philo->shared->sem_printf);
	printf("%s%ld %d %s%s\n", color, elapsed_time(philo->infos),
		philo->id, msg, RESET);
	if (state != DEAD)
		sem_post(philo->shared->sem_printf);
}
