/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:01:31 by gavivas-          #+#    #+#             */
/*   Updated: 2025/08/20 20:53:58 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_all(int n_philos, int argc, char **args)
{
	t_philo	*philos;
	t_data	data;

	philos = malloc(sizeof(t_philo) * n_philos);
	if (!philos)
		return (printf(MALLOC_ER), 1);
	init_data(&data, args, argc - 1);
	if (init_mutex(&data))
		return (free(philos), printf(MUTEX_ERR), 1);
	if (init_forks(&data))
		return (destroy_mutex(philos), EXIT_FAILURE);
	data.start_time = get_time_ms();
	data.stop_simulation = 0;
	init_philos(philos, n_philos, &data);
	if (n_philos == 1)
		return (a_philo_die(philos), EXIT_FAILURE);
	if (init_threads(philos, n_philos))
		return (destroy_all(philos), printf(THREADS_ER), EXIT_FAILURE);
	if (wait_threads(philos, n_philos))
		return (destroy_all(philos), printf(FORKS_ERR_2), EXIT_FAILURE);
	destroy_all(philos);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **args)
{
	int		n_philos;

	if (argc < 5 || argc > 6)
		return (printf(ARGC_ERROR), 1);
	if (args[1][0] <= 32)
		return (printf(ARGS_ERROR), 1);
	n_philos = ft_atoi(args[1]);
	if (n_philos < 1 || n_philos > 200)
		return (printf(N_ERROR), 1);
	return (init_all(n_philos, argc, args));
}
