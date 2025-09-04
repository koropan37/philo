/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:06:20 by skimura           #+#    #+#             */
/*   Updated: 2025/09/01 19:40:57 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	table;
	t_philo	philo[PHILO_MAX];

	memset(&table, 0, sizeof(table));
	memset(philo, 0, sizeof(philo));
	if (parse(ac, av, &table) != 0)
		return (1);
	init_table(&table, philo);
	if (init_philo(&table, philo) != 0)
		return (1);
	if (dining(&table) != 0)
		return (1);
	return (0);
}
