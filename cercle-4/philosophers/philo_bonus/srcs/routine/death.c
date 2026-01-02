/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 11:00:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_monitor(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		sem_wait(&p->meal_lock);
		if ((size_t)(now() - p->last_meal) >= p->rules->time_to_die)
		{
			sem_wait(p->rules->print);
			printf("%lu %d %s\n", now() - p->sim_start, p->id, "died");
			fflush(stdout);
			sem_post(p->rules->stop);
			return (NULL);
		}
		sem_post(&p->meal_lock);
		usleep(50);
	}
	return (NULL);
}
