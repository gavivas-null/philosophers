/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:42:43 by gavivas-          #+#    #+#             */
/*   Updated: 2025/07/24 21:36:32 by gavivas-         ###   ########.fr       */
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
# define N_ERROR "Error, the number of philosophers must be greater than 1.\n"
# define MALLOC_ER "Error allocating memory with (malloc).\n"

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

void	debug_philo(t_philo *philos, int n_philos); // función para debugear.

// ------------------------------------error------------------------------------

// ------------------------------------init------------------------------------
void	init_philos(t_philo *philos, int n_philos, t_data *data);

// ------------------------------------philo------------------------------------

// ------------------------------------print------------------------------------

// -----------------------------------routine-----------------------------------

// ------------------------------------utils------------------------------------
int		ft_atoi(const char *str);
long	get_time_ms(void);
void	smart_sleep(long time_to_wait, t_data *data);

#endif