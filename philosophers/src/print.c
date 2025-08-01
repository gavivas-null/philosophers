/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:48:20 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/01 19:48:09 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
