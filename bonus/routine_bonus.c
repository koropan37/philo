/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:31:52 by skimura           #+#    #+#             */
/*   Updated: 2025/08/28 22:24:52 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	wait_start(t_philo *philo);

void	philo_routine(t_philo *philo)
{
	wait_start(philo);
	philo_monitoring(philo);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->num_of_philo % 2)
			my_usleep(philo->waiting_time / 2);
	}
	exit(1);
}

static void	wait_start(t_philo *philo)
{
	if (philo->num_of_philo == 1)
		return ;
	if (philo->num_of_philo % 2)
		my_usleep(philo->waiting_time * (philo->id - 1));
	else if (philo->num_of_philo / 2 < (philo->id - 1))
		my_usleep(philo->waiting_time);
}
