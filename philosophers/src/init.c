/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:33:49 by gavivas-          #+#    #+#             */
/*   Updated: 2025/07/25 19:06:20 by gavivas-         ###   ########.fr       */
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
		philos[i].last_meal_time = 0;
		i++;
	}
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
	return (0);
}

void	wait_threads(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
