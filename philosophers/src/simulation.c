/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:23:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/04 16:59:34 by gavivas-         ###   ########.fr       */
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
	while ((philo->data->must_eat == -1 || i < philo->data->must_eat)
		&& !philo->data->stop_simulation)
	{
		smart_sleep((philo->id) * 2, philo->data);
		is_thinking(philo);
		if (philo->data->n_philos == 1)
		{
			a_philo_die(philo);
			break ;
		}
		has_taken_a_fork(philo);
		is_sleeping(philo);
		i++;
	}
	return (NULL);
}
