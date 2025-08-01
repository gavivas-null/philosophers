/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:23:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/01 20:06:40 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	is_thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
	smart_sleep(100, philo->data);
}

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

void	is_eating(t_philo *philo)
{
	philo->last_meal_time = get_time_ms();
	print_state(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
}

void	is_sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
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
		is_thinking(philo);
		has_taken_a_fork(philo);
		is_sleeping(philo);
		i++;
	}
	return (NULL);
}
