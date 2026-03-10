/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:03:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Monitor philosopher death based on time since last meal.
 * @param arg Pointer to philosopher struct (cast from void*).
 * @return NULL when monitoring ends.
 *
 * Waits for meal_lock, checks time, prints status and signals stop if dead.
 */
void	*death_monitor(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		sem_wait(&p->meal_lock);
		if ((size_t)(now() - p->last_meal) >= p->rules->time_to_die)
		{
			print_status(p, "died");
			sem_post(p->rules->stop);
			exit(1);
		}
		sem_post(&p->meal_lock);
		usleep(50);
	}
	return (NULL);
}
