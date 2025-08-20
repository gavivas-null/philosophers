/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:23:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/20 20:54:16 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	has_taken_a_fork(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
		is_eating(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		is_eating(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		smart_sleep(philo->data->time_to_eat / 2, philo->data);
	while (1)
	{
		is_thinking(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->stop_simulation)
			return (pthread_mutex_unlock(&philo->data->data_mutex), NULL);
		pthread_mutex_unlock(&philo->data->data_mutex);
		has_taken_a_fork(philo);
		is_sleeping(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->stop_simulation)
			return (pthread_mutex_unlock(&philo->data->data_mutex), NULL);
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	return (NULL);
}
