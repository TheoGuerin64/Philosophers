/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:00 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/23 18:01:26 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	get_sign(const char *nptr, int begin)
{
	if (nptr[begin] == '-')
		return (-1);
	return (1);
}

static int	first_non_white_space(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	return (i);
}

static int	is_overflow(int result, int old_result, int sign)
{
	if (sign == -1 && result == INT_MIN)
		return (0);
	return (result / 10 != old_result);
}

int	ft_atoi(const char *nptr, int *error_flag)
{
	int	result;
	int	old_result;
	int	sign;
	int	i;

	i = first_non_white_space(nptr);
	sign = get_sign(nptr, i);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	result = 0;
	old_result = 0;
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += nptr[i] - '0';
		if (is_overflow(result, old_result, sign))
		{
			*error_flag = 1;
			return (-1 + (sign == -1));
		}
		old_result = result;
		i++;
	}
	return (result * sign);
}
