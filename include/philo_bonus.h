/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:31:04 by skimura           #+#    #+#             */
/*   Updated: 2025/08/28 22:24:00 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int			id;
	int			eaten;
	int			finished;
	pthread_t	own_monitor;
	int			num_of_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			must_eat;
	size_t		start_time;
	size_t		last_meal;
	double		waiting_time;
	int			*dead;
	sem_t		*forks;
	sem_t		*dead_sem;
	sem_t		*print_sem;
	sem_t		*meal_sem;
	sem_t		*start_sem;

}				t_philo;

typedef struct s_table
{
	pid_t		*pids;
	int			dead_flag;
	size_t		start_time;
	int			num_of_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			must_eat;
	sem_t		*forks;
	sem_t		*dead_sem;
	sem_t		*print_sem;
	sem_t		*meal_sem;
	sem_t		*start_sem;

}				t_table;

// parse
void			parse(int ac, char *av[], t_table *table);
// utils
int				ft_isdigit(int c);
int				ft_atoi(const char *nptr);
size_t			get_time_of_now(void);
int				my_usleep(size_t ms);
void			print_philo(t_philo *philo, int id, char *str);
void			print_death(t_philo *philo, int id);
// init
void			init_philo(t_table *table, t_philo *philo);
void			init_table(t_table *table);
// clean_up
void			close_all_sem(t_table *table);
void			free_close_exit(t_table *table);
// action
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
// dining
void			dining(t_table *table);
void			philo_monitoring(t_philo *philo);
void			philo_routine(t_philo *philo);
#endif
