/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:00:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Entry point for simulation setup and thread management.
 * @param rules Pointer to rules struct.
 *
 * Initializes mutexes, philosopher data, threads, monitor, and handles cleanup.
 */
void	philo(t_rules *rules)
{
	pthread_t		philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	t_philo			data[MAX_PHILOS];
	pthread_t		monitor;

	init_mutexes(rules, forks);
	create_philos(rules, data, forks, philos);
	pthread_create(&monitor, NULL, monitor_routine, data);
	join_threads(rules, philos, monitor);
	destroy_mutexes(rules, forks);
}

/**
 * @brief Main routine for each philosopher thread.
 * @param arg Pointer to philosopher struct (cast from void*).
 * @return NULL when routine ends.
 *
 * Loops through eating, sleeping, thinking, and death checks.
 */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(10);
	while (1)
	{
		if (check_dead_flag(philo))
			break ;
		if (philo_eat(philo))
			break ;
		if (check_dead_flag(philo))
			break ;
		philo_sleep(philo);
		if (check_dead_flag(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
