/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:15:28 by skimura           #+#    #+#             */
/*   Updated: 2025/09/04 19:58:40 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	judge_philo_dead(t_philo *philo, size_t time_to_die);
static int	philo_dead(t_philo *philo);
static int	eaten_all(t_philo *philo);

void	*monitoring(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if (philo_dead(philo))
		{
			my_usleep(1);
			break ;
		}
		if (eaten_all(philo))
		{
			pthread_mutex_lock(philo->print_mutex);
			printf("/* All philo is full */\n");
			pthread_mutex_unlock(philo->print_mutex);
			break ;
		}
		my_usleep(1);
	}
	return (NULL);
}

static int	judge_philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (get_time_of_now() - philo->last_meal >= time_to_die
		&& philo->eating == FINISH)
		return (pthread_mutex_unlock(philo->meal_mutex), 1);
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

static int	philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		if (judge_philo_dead(&philo[i], philo[i].time_to_die))
		{
			print_death(&philo[i], philo[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	eaten_all(t_philo *philo)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philo->must_eat == -1)
		return (0);
	while (i < philo->num_of_philo)
	{
		pthread_mutex_lock(philo[i].meal_mutex);
		if (philo[i].eaten >= philo->must_eat)
			finished_eating++;
		pthread_mutex_unlock(philo[i].meal_mutex);
		i++;
	}
	if (finished_eating == philo->num_of_philo)
	{
		pthread_mutex_lock(philo->dead_mutex);
		*philo->dead = FULL;
		pthread_mutex_unlock(philo->dead_mutex);
		return (1);
	}
	return (0);
}

void	print_death(t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(philo->dead_mutex);
	if (!*philo->dead)
	{
		time = get_time_of_now() - philo->start_time;
		printf("%zu %d is died\n", time, id);
		*philo->dead = DEAD;
	}
	pthread_mutex_unlock(philo->dead_mutex);
	pthread_mutex_unlock(philo->print_mutex);
}
