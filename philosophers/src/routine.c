/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:33:43 by gavivas-          #+#    #+#             */
/*   Updated: 2025/07/25 21:20:50 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("🧠 Filósofo %d está pensando\n", philo->id);
	smart_sleep(200, philo->data);
	printf("🍝 Filósofo %d está comiendo\n", philo->id);
	smart_sleep(200, philo->data);
	printf("💤 Filósofo %d está durmiendo\n", philo->id);
	smart_sleep(200, philo->data);
	return (NULL);
}
