/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:59:36 by skimura           #+#    #+#             */
/*   Updated: 2025/08/23 16:19:54 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eating;
	int				eaten;
	int				num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat;
	size_t			start_time;
	size_t			last_meal;
	int				*start;
	int				*dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*start_mutex;
}					t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_t		monitor;
	int				dead_flag;
	int				start_flag;
	int				num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	forks[PHILO_MAX];

}					t_table;

int					parse(int ac, char *av[], t_table *table);
// utils
int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
size_t				get_time_of_now(void);
int					my_usleep(size_t ms);
void				print_philo(t_philo *philo, int id, char *str);
void				print_death(t_philo *philo, int id);

// init
void				init_table(t_table *table, t_philo *philo);
int					init_philo(t_table *table, t_philo *philo);
// action
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
// dining
int					dining(t_table *table);
int					is_dead(t_philo *philo);
void				*monitoring(void *p);
void				*routine(void *p);

#endif
