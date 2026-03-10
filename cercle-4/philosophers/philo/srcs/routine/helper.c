/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:27:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:00:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initialize mutexes for forks and shared state.
 * @param rules Pointer to rules struct.
 * @param forks Array of fork mutexes.
 *
 * Initializes dead_lock, meal_lock, and all fork mutexes.
 */
void	init_mutexes(t_rules *rules, pthread_mutex_t *forks)
{
	size_t	i;

	pthread_mutex_init(&rules->dead_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
	rules->dead_flag = 0;
	i = 0;
	while (i < rules->nb_philo)
		pthread_mutex_init(&forks[i++], NULL);
}

/**
 * @brief Create philosopher threads and initialize their data.
 * @param rules Pointer to rules struct.
 * @param data Array of philosopher structs.
 * @param forks Array of fork mutexes.
 * @param philos Array of thread IDs.
 *
 * Sets up philosopher data and launches threads.
 */
void	create_philos(t_rules *rules, t_philo *data, pthread_mutex_t *forks,
		pthread_t *philos)
{
	size_t	i;
	size_t	sim_start;

	sim_start = now();
	i = 0;
	while (i < rules->nb_philo)
	{
		data[i].id = i + 1;
		data[i].sim_start = sim_start;
		data[i].last_meal = sim_start;
		data[i].meals_eaten = 0;
		data[i].rules = rules;
		data[i].left_f = &forks[i];
		data[i].right_f = &forks[(i + 1) % rules->nb_philo];
		pthread_create(&philos[i], NULL, philo_routine, &data[i]);
		i++;
	}
}

/**
 * @brief Join philosopher threads and monitor thread.
 * @param rules Pointer to rules struct.
 * @param philos Array of thread IDs.
 * @param monitor Monitor thread ID.
 *
 * Waits for all philosopher threads and monitor to finish.
 */
void	join_threads(t_rules *rules, pthread_t *philos, pthread_t monitor)
{
	size_t	i;

	i = 0;
	while (i < rules->nb_philo)
		pthread_join(philos[i++], NULL);
	pthread_join(monitor, NULL);
}

/**
 * @brief Destroy all mutexes used in the simulation.
 * @param rules Pointer to rules struct.
 * @param forks Array of fork mutexes.
 *
 * Destroys fork mutexes, dead_lock, and meal_lock.
 */
void	destroy_mutexes(t_rules *rules, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (i < rules->nb_philo)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&rules->dead_lock);
	pthread_mutex_destroy(&rules->meal_lock);
}
