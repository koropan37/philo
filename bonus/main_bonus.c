/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:30:30 by skimura           #+#    #+#             */
/*   Updated: 2025/08/27 18:46:24 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int ac, char *av[])
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	parse(ac, av, &table);
	init_table(&table);
	dining(&table);
	return (EXIT_SUCCESS);
}
