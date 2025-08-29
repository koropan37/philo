/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:23:00 by skimura           #+#    #+#             */
/*   Updated: 2025/08/27 18:26:42 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	close_all_sem(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->dead_sem);
	sem_close(table->start_sem);
	sem_close(table->print_sem);
	sem_close(table->meal_sem);
}

void	free_close_exit(t_table *table)
{
	free(table->pids);
	close_all_sem(table);
	exit(EXIT_FAILURE);
}
