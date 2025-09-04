/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:39:21 by skimura           #+#    #+#             */
/*   Updated: 2025/09/04 20:02:04 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_table(t_table *table)
{
	table->dead_flag = 0;
	table->pids = malloc(sizeof(pid_t) * table->num_of_philo);
	if (!table->pids)
	{
		write(2, "alloc error\n", 13);
		exit(EXIT_FAILURE);
	}
	table->forks = sem_open("/forks", O_CREAT, 600, table->num_of_philo);
	sem_unlink("/forks");
	table->dead_sem = sem_open("/dead", O_CREAT, 600, 1);
	sem_unlink("/dead");
	table->print_sem = sem_open("/print", O_CREAT, 600, 1);
	sem_unlink("/print");
	table->meal_sem = sem_open("/meal", O_CREAT, 600, 1);
	sem_unlink("/meal");
}
