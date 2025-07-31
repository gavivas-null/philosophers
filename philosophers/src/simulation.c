/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:23:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/07/31 22:11:59 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_state(t_philo *philo, char *msg)
{
	long	start;
	long	time;

	start = get_time_ms();
	time = start - (philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("[%ld] %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

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

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while ((philo->data->must_eat == -1 || i < philo->data->must_eat)
		&& !philo->data->stop_simulation)
	{
		if ((philo->id % 2) == 0)
			smart_sleep(philo->data->time_to_eat / 2, philo->data);
		print_state(philo, "is thinking");
		smart_sleep(220, philo->data);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		philo->last_meal_time = get_time_ms();
		print_state(philo, "is eating");
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		smart_sleep(philo->data->time_to_eat, philo->data);
		print_state(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo->data);
		i++;
	}
	return (NULL);
}
