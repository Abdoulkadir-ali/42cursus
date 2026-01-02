/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 09:42:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->rules->time_to_eat / 2);
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
