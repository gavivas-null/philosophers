/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:50:10 by gavivas-          #+#    #+#             */
/*   Updated: 2025/09/22 17:26:57 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_cycle(t_philo *philo, int n_philo, int *full)
{
	int		i;
	long	now;

	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		now = get_time_ms();
		if (now - philo[i].last_meal_time > philo[i].data->time_to_die)
		{
			philo->data->stop_simulation = 1;
			pthread_mutex_unlock(&philo->data->data_mutex);
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("[%ld] %d %s\n", now - philo->data->start_time,
				philo[i].id, "died");
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (EXIT_FAILURE);
		}
		if (philo->data->must_eat > 0
			&& philo[i].meal_count >= philo->data->must_eat)
			*full = *full + 1;
		pthread_mutex_unlock(&philo->data->data_mutex);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	monitor_deaths(t_philo *philo, int n_philo)
{
	int	full;

	while (!is_dead(philo))
	{
		full = 0;
		if (check_cycle(philo, n_philo, &full) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (philo->data->must_eat > 0 && full == n_philo)
		{
			pthread_mutex_lock(&philo->data->data_mutex);
			philo->data->stop_simulation = 1;
			pthread_mutex_unlock(&philo->data->data_mutex);
			return (EXIT_SUCCESS);
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	monitor_deaths(philos, philos[0].data->n_philos);
	return (NULL);
}

void	a_philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_state(philo, "has taken a fork");
	smart_sleep(philo->data->time_to_die, philo->data);
	print_state(philo, "died");
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->data->stop_simulation = 1;
	pthread_mutex_unlock(&philo->data->data_mutex);
	destroy_all(philo);
}
