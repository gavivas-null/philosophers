/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:42:43 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/21 20:48:57 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ARGC_ERROR "Error, the number of arguments is not valid.\n"
# define ARGS_ERROR "Error, the argument is null or empty.\n"
# define N_ERROR "Error, the number of philos must be between 1 and 200.\n"
# define MALLOC_ER "Error allocating memory with (malloc).\n"
# define THREADS_ER "Error creating threads.\n"
# define DATA_ERR "Error filling in the data.\n"
# define MUTEX_ERR "Error initializing mutexes.\n"
# define MUTEX_ERR_2 "Error destroying mutexes.\n"
# define FORKS_ERR "Error initializing forks.\n"
# define FORKS_ERR_2 "Error waiting forks.\n"

typedef struct s_data
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			start_time;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	pthread_t		monitor_thread;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meal_count;
	long			last_meal_time;
	t_data			*data;
	pthread_t		thread;
}				t_philo;

// ------------------------------------init------------------------------------
int		init_all(int n_philos, int argc, char **args);
void	init_philos(t_philo *philos, int n_philos, t_data *data);
int		init_data(t_data *data, char **args, int len_argc);
int		init_threads(t_philo *philos, int n_philos);
int		init_mutex(t_data *data);
int		init_forks(t_data *data);

// ---------------------------------simulation---------------------------------
void	is_thinking(t_philo *philo);
void	has_taken_a_fork(t_philo *philo);
void	is_eating(t_philo *philo);
void	is_sleeping(t_philo *philo);
void	*routine(void *arg);

// -----------------------------------monitor-----------------------------------
void	*monitor_routine(void *arg);
int		check_cycle(t_philo *philo, int n_philo, int *full);
int		monitor_deaths(t_philo *philo, int n_philo);
void	a_philo_die(t_philo *philo);

// ------------------------------------print------------------------------------
void	print_state(t_philo *philo, char *msg);

// ------------------------------------utils------------------------------------
int		ft_atoi(const char *str);
long	get_time_ms(void);
void	smart_sleep(long time_to_wait, t_data *data);
int		wait_threads(t_philo *philos, int n_philos);
int		is_dead(t_philo *philo);
int		destroy_all(t_philo *philo);
int		destroy_mutex(t_philo *philo);

#endif