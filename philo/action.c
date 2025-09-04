/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:04:16 by skimura           #+#    #+#             */
/*   Updated: 2025/09/04 19:56:08 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	select_fork(t_philo *philo);

void	print_philo(t_philo *philo, int id, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->dead == DEAD)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	time = get_time_of_now() - philo->start_time;
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->dead_mutex);
	pthread_mutex_unlock(philo->print_mutex);
}

void	sleeping(t_philo *philo)
{
	print_philo(philo, philo->id, "is sleeping");
	my_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_philo(philo, philo->id, "is thinking");
	if (philo->num_of_philo % 2 != 0)
		my_usleep(philo->time_to_eat / 10);
}

void	eating(t_philo *philo)
{
	if (select_fork(philo) == 1)
		return ;
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->meal_mutex);
	philo->eating = EATING;
	print_philo(philo, philo->id, "is eating");
	philo->last_meal = get_time_of_now();
	philo->eaten++;
	philo->eating = FINISH;
	pthread_mutex_unlock(philo->meal_mutex);
	my_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static int	select_fork(t_philo *philo)
{
	if (philo->num_of_philo == 1)
	{
		print_philo(philo, philo->id, "has taken a fork");
		my_usleep(philo->time_to_die);
		print_death(philo, philo->id);
		return (1);
	}
	else
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			print_philo(philo, philo->id, "has taken a left fork");
			pthread_mutex_lock(philo->right_fork);
			print_philo(philo, philo->id, "has taken a right fork");
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			print_philo(philo, philo->id, "has taken a right fork");
			pthread_mutex_lock(philo->left_fork);
			print_philo(philo, philo->id, "has taken a left fork");
		}
		return (0);
	}
}
