/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:33:53 by gavivas-          #+#    #+#             */
/*   Updated: 2025/07/24 21:20:32 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// funcion para debugear, se debe borrar antes de la entrega.
void	debug_philo(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		printf("Filosofo %d: left = %d, right = %d\n", i + 1,
			philos[i].left_fork, philos[i].right_fork);
		i++;
	}
}
