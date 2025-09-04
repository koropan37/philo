/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:17:50 by skimura           #+#    #+#             */
/*   Updated: 2025/09/04 20:00:53 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_philo *philo);
static void	even_case(t_philo *philo);
static void	odd_case(t_philo *philo);
int			is_dead(t_philo *philo);

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	wait_start(philo);
	while (1)
	{
		if (is_dead(philo))
			break ;
		eating(philo);
		if (is_dead(philo))
			break ;
		sleeping(philo);
		if (is_dead(philo))
			break ;
		thinking(philo);
	}
	return (NULL);
}

static void	wait_start(t_philo *philo)
{
	if (philo->num_of_philo == 1)
		return ;
	if ((philo->num_of_philo % 2) == 0)
		even_case(philo);
	else
		odd_case(philo);
}

static void	even_case(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
		my_usleep(philo->time_to_eat / 2);
}

static void	odd_case(t_philo *philo)
{
	size_t	wait_time;

	if ((philo->id - 1) % 2 == 0)
		wait_time = philo->time_to_eat / (philo->num_of_philo - 1) * (philo->id
				- 1);
	else
		wait_time = philo->time_to_eat / (philo->num_of_philo - 1)
			* ((philo->num_of_philo - 1) + (philo->id - 1));
	my_usleep(wait_time);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->dead == DEAD || *philo->dead == FULL)
		return (pthread_mutex_unlock(philo->dead_mutex), 1);
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);
}
