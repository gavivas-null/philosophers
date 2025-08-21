/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:33:57 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/21 19:28:17 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	i;
	int	sign;

	a = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - '0');
		i++;
	}
	return (a * sign);
}

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(long time_to_wait, t_data *data)
{
	long	start_time;

	(void)data;
	start_time = get_time_ms();
	while (get_time_ms() - start_time < time_to_wait)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->data_mutex);
		usleep(100);
	}
}

int	wait_threads(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_join(philos[0].data->monitor_thread, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
