/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:23:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/01 18:50:06 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
