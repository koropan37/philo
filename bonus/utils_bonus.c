/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:23:52 by skimura           #+#    #+#             */
/*   Updated: 2025/08/28 19:00:24 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoi(const char *nptr)
{
	long	result;

	if (!nptr)
		return (0);
	result = 0;
	while (*nptr)
	{
		if (result > ((long)INT_MAX - (*nptr - '0')) / 10)
			return (0);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (result > INT_MAX)
		return (0);
	return ((int)(result));
}

size_t	get_time_of_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday error\n", 20);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	my_usleep(size_t ms)
{
	size_t	start;
	size_t	now;

	start = get_time_of_now();
	while (1)
	{
		now = get_time_of_now();
		if (now - start >= ms)
			break ;
		usleep(10);
	}
	return (0);
}
