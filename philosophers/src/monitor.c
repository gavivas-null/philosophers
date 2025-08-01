/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:50:10 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/01 18:50:37 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	monitor_deaths(t_philo *philo, int n_philo)
{
	int		i;
	long	now;

	while (!philo->data->stop_simulation)
	{
		i = 0;
		now = get_time_ms();
		while (i < n_philo)
		{
			if (now - philo[i].last_meal_time > philo[i].data->time_to_die)
			{
				pthread_mutex_lock(&philo->data->data_mutex);
				printf("[%ld] %d %s\n", now - philo->data->start_time,
					philo[i].id, "died");
				philo->data->stop_simulation = 1;
				pthread_mutex_unlock(&philo->data->data_mutex);
				return (1);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	monitor_deaths(philos, philos[0].data->n_philos);
	return (NULL);
}
