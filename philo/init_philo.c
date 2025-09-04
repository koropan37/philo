/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:55:30 by skimura           #+#    #+#             */
/*   Updated: 2025/09/01 19:40:48 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_from_table(t_table *table, t_philo *philo, int i);

int	init_philo(t_table *table, t_philo *philo)
{
	int		i;
	size_t	start_time;

	i = 0;
	start_time = get_time_of_now();
	if (start_time == (size_t)-1)
		return (1);
	while (i < table->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].eaten = 0;
		philo[i].start_time = start_time;
		philo[i].last_meal = start_time;
		init_philo_from_table(table, &philo[i], i);
		i++;
	}
	return (0);
}

static void	init_philo_from_table(t_table *table, t_philo *philo, int i)
{
	philo->num_of_philo = table->num_of_philo;
	philo->time_to_die = table->time_to_die;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	philo->must_eat = table->must_eat;
	philo->print_mutex = &table->print_mutex;
	philo->dead_mutex = &table->dead_mutex;
	philo->meal_mutex = &table->meal_mutex;
	philo->start_mutex = &table->start_mutex;
	philo->start = &table->start_flag;
	philo->dead = &table->dead_flag;
	philo->left_fork = &table->forks[i];
	if (i == 0)
		philo->right_fork = &table->forks[table->num_of_philo - 1];
	else
		philo->right_fork = &table->forks[i - 1];
}
