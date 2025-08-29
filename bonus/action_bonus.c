/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:33:18 by skimura           #+#    #+#             */
/*   Updated: 2025/08/28 20:38:23 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	select_fork(t_philo *philo);

void	print_philo(t_philo *philo, int id, char *str)
{
	size_t	time;

	sem_wait(philo->dead_sem);
	sem_wait(philo->print_sem);
	if (*philo->dead == 1)
		return ;
	time = get_time_of_now() - philo->start_time;
	printf("%zu %d %s\n", time, id, str);
	sem_post(philo->print_sem);
	sem_post(philo->dead_sem);
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
	sem_wait(philo->meal_sem);
	print_philo(philo, philo->id, "is eating");
	philo->last_meal = get_time_of_now();
	philo->eaten++;
	if (philo->must_eat > 0 && philo->eaten >= philo->must_eat)
	{
		philo->finished = 1;
		sem_post(philo->meal_sem);
		sem_post(philo->forks);
		sem_post(philo->forks);
		exit(0);
	}
	sem_post(philo->meal_sem);
	my_usleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
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
	sem_wait(philo->forks);
	print_philo(philo, philo->id, "has taken a fork");
	sem_wait(philo->forks);
	print_philo(philo, philo->id, "has taken a fork");
	return (0);
}
