/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:23:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/07/28 19:53:57 by gavivas-         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_state(philo, "is thinking");
	smart_sleep(50, philo->data);
	print_state(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
	print_state(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	return (NULL);
}
