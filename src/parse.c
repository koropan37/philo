/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:43:34 by skimura           #+#    #+#             */
/*   Updated: 2025/08/19 23:08:49 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	validate(int ac, char *av[]);
static int	usage_error(void);
static int	allow_digits(int ac, char *av[], t_table *table);
static void	atoi_args(int ac, char *av[], t_table *table);

int	parse(int ac, char *av[], t_table *table)
{
	if (validate(ac, av) != 0)
		return (1);
	if (allow_digits(ac, av, table) != 0)
		return (1);
	return (0);
}

static int	validate(int ac, char *av[])
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (usage_error());
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				write(2, "Arguments allowed only digits", 28);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	usage_error(void)
{
	write(2, "Usage: ./philo <num_of_philo> <die> <eat> <sleep> (must_eat)\n",
		62);
	return (1);
}

static int	allow_digits(int ac, char *av[], t_table *table)
{
	atoi_args(ac, av, table);
	if (table->num_of_philo <= 0 || table->num_of_philo > PHILO_MAX
		|| table->time_to_die <= 0 || table->time_to_eat <= 0
		|| table->time_to_sleep <= 0)
	{
		if (table->num_of_philo <= 0 || table->num_of_philo > PHILO_MAX)
			write(2, "Invalid number_of_philosophers\n", 32);
		if (table->time_to_die <= 0)
			write(2, "Invalid time_to_die\n", 21);
		if (table->time_to_eat <= 0)
			write(2, "Invalid time_to_eat\n", 21);
		if (table->time_to_sleep <= 0)
			write(2, "Invalid time_to_sleep\n", 23);
		return (1);
	}
	if (ac == 6)
	{
		if (table->must_eat <= 0)
		{
			write(2, "Invalid number_of_times_each_philosopher_must_eat\n", 51);
			return (1);
		}
	}
	return (0);
}

static void	atoi_args(int ac, char *av[], t_table *table)
{
	table->num_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	else
		table->must_eat = -1;
}
