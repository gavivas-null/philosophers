/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:48:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/21 20:09:41 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_state(t_philo *philo, char *msg)
{
	long	start;
	long	time;

	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	start = get_time_ms();
	time = start - (philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("[%ld] %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_state(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->meal_count = philo->meal_count + 1;
	pthread_mutex_unlock(&philo->data->data_mutex);
}

void	is_sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

void	is_thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
}
