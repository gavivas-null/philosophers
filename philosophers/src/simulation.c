/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:23:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/19 19:36:29 by gavivas-         ###   ########.fr       */
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
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->data->n_philos == 1)
		return (a_philo_die(philo), NULL);
	if ((philo->id % 2) == 0)
		smart_sleep(philo->data->time_to_eat / 2, philo->data);
	while (philo->data->must_eat == -1 || i < philo->data->must_eat)
	{
		if (i >= philo->data->must_eat)
		{
			pthread_mutex_lock(&philo->data->data_mutex);
			philo->finished = 1;
			philo->data->done_count++;
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		is_thinking(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		has_taken_a_fork(philo);
		is_sleeping(philo);
		i++;
	}
	return (NULL);
}
