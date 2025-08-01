/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:33:49 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/01 21:14:48 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philos(t_philo *philos, int n_philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % n_philos;
		philos[i].meal_count = 0;
		philos[i].last_meal_time = data->start_time;
		i++;
	}
}

int	init_data(t_data *data, char **args, int len_argc)
{
	data->n_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	data->must_eat = -1;
	if (len_argc == 5)
	{
		data->must_eat = ft_atoi(args[5]);
	}
	return (0);
}

int	init_threads(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&philos[0].data->monitor_thread, NULL,
			monitor_routine, &philos[0]) != 0)
		return (1);
	return (0);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
