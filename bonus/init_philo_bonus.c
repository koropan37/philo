/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:04:47 by skimura           #+#    #+#             */
/*   Updated: 2025/08/28 22:24:11 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	init_philo(t_table *table, t_philo *philo)
{
	size_t	start_time;

	start_time = get_time_of_now();
	if (start_time == (size_t)-1)
		exit(EXIT_FAILURE);
	philo->start_time = start_time;
	philo->last_meal = start_time;
	philo->id = 0;
	philo->eaten = 0;
	philo->finished = 0;
	philo->num_of_philo = table->num_of_philo;
	philo->time_to_die = table->time_to_die;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	philo->must_eat = table->must_eat;
	philo->waiting_time = table->time_to_eat / (double)(table->num_of_philo / 2);
	philo->dead = &table->dead_flag;
	philo->forks = table->forks;
	philo->dead_sem = table->dead_sem;
	philo->print_sem = table->print_sem;
	philo->meal_sem = table->meal_sem;
	philo->start_sem = table->start_sem;
}
