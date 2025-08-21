/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:04:50 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/21 20:28:28 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	destroy_mutex(t_philo *philo)
{
	if (pthread_mutex_destroy(&philo->data->print_mutex))
		return (printf(MUTEX_ERR_2), EXIT_FAILURE);
	if (pthread_mutex_destroy(&philo->data->data_mutex))
		return (printf(MUTEX_ERR_2), EXIT_FAILURE);
	free(philo);
	return (EXIT_SUCCESS);
}

int	destroy_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
	{
		if (pthread_mutex_destroy(&philo->data->forks[i++]))
			return (printf(MUTEX_ERR_2), EXIT_FAILURE);
	}
	if (destroy_mutex(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
