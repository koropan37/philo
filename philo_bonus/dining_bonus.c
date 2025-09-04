/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:33:03 by skimura           #+#    #+#             */
/*   Updated: 2025/09/03 18:25:10 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_child(t_table *table, t_philo *philo);
static void	wait_philo(t_table *table);
static void	stop_table(t_table *table);

void	dining(t_table *table)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(philo));
	init_philo(table, &philo);
	philo_child(table, &philo);
	wait_philo(table);
	close_all_sem(table);
	free(table->pids);
}

static void	philo_child(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		philo->id = i + 1;
		table->pids[i] = fork();
		if (table->pids[i] < 0)
		{
			write(2, "Error: fork", 12);
			free_close_exit(table);
		}
		if (table->pids[i] == 0)
			philo_routine(philo);
		i++;
	}
}

static void	wait_philo(t_table *table)
{
	int	status;
	int	count;

	count = 0;
	while (count < table->num_of_philo)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			stop_table(table);
			table->dead_flag = 1;
			break ;
		}
		count++;
	}
	if (!table->dead_flag && count == table->num_of_philo)
		printf("/* All philo is full */\n");
}

static void	stop_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		if (table->pids[i] > 0)
			kill(table->pids[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < table->num_of_philo)
	{
		if (table->pids[i] > 0)
			waitpid(table->pids[i], NULL, 0);
		i++;
	}
}
