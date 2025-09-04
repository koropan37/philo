/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:32:47 by skimura           #+#    #+#             */
/*   Updated: 2025/09/03 17:42:50 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitoring(t_philo *philo);
void		print_death(t_philo *philo, int id);

void	philo_monitoring(t_philo *philo)
{
	if (pthread_create(&philo->own_monitor, NULL, (void *)monitoring, philo))
	{
		write(2, "error: pthread_create\n", 23);
		exit(EXIT_FAILURE);
	}
	pthread_detach(philo->own_monitor);
}

static void	*monitoring(t_philo *philo)
{
	size_t	now;

	while (1)
	{
		sem_wait(philo->meal_sem);
		if (philo->finished)
		{
			sem_post(philo->meal_sem);
			return (NULL);
		}
		now = get_time_of_now();
		if (philo->last_meal > 0 && philo->last_meal + philo->time_to_die < now)
		{
			sem_post(philo->meal_sem);
			print_death(philo, philo->id);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->meal_sem);
		my_usleep(1);
	}
	return (NULL);
}

void	print_death(t_philo *philo, int id)
{
	size_t	time;

	sem_wait(philo->dead_sem);
	sem_wait(philo->print_sem);
	if (!*philo->dead)
	{
		time = get_time_of_now() - philo->start_time;
		printf("%zu %d is died\n", time, id);
		*philo->dead = DEAD;
	}
	sem_post(philo->print_sem);
}
