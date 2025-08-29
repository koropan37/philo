/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:26:32 by skimura           #+#    #+#             */
/*   Updated: 2025/08/20 19:22:17 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*routine(void *p);
void		*monitoring(void *p);
static int	monitoring_threads(t_table *table);
static int	philo_threads(t_table *table);
static void	destroy_table(t_table *table);

int	dining(t_table *table)
{
	int	i;

	if (monitoring_threads(table) != 0)
		return (1);
	if (philo_threads(table) != 0)
		return (1);
	if (pthread_join(table->monitor, NULL) != 0)
	{
		write(2, "error: pthread_join\n", 21);
		destroy_table(table);
		return (1);
	}
	i = 0;
	while (i < table->num_of_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
		{
			write(2, "error: pthread_join\n", 21);
			destroy_table(table);
			return (1);
		}
		i++;
	}
	destroy_table(table);
	return (0);
}

static int	monitoring_threads(t_table *table)
{
	if (pthread_create(&table->monitor, NULL, &monitoring, table->philo) != 0)
	{
		write(2, "error: pthread_create\n", 23);
		destroy_table(table);
		return (1);
	}
	return (0);
}

static int	philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &routine,
				&table->philo[i]) != 0)
		{
			write(2, "error: pthread_create\n", 23);
			destroy_table(table);
			return (1);
		}
		i++;
	}
	pthread_mutex_lock(&table->start_mutex);
	table->start_flag = 1;
	pthread_mutex_unlock(&table->start_mutex);
	return (0);
}

static void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->start_mutex);
	while (i < table->num_of_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
