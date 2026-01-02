/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:27:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 03:08:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_rules *rules, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_init(&rules->dead_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
	rules->dead_flag = 0;
	i = 0;
	while (i < rules->nb_philo)
		pthread_mutex_init(&forks[i++], NULL);
}

void	create_philos(t_rules *rules, t_philo *data, pthread_mutex_t *forks,
		pthread_t *philos)
{
	int		i;
	size_t	sim_start;

	sim_start = now();
	i = 0;
	while (i < rules->nb_philo)
	{
		data[i].id = i + 1;
		data[i].sim_start = sim_start;
		data[i].last_meal = sim_start;
		data[i].rules = rules;
		data[i].left_f = &forks[i];
		data[i].right_f = &forks[(i + 1) % rules->nb_philo];
		pthread_create(&philos[i], NULL, philo_routine, &data[i]);
		i++;
	}
}

void	join_threads(t_rules *rules, pthread_t *philos, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
		pthread_join(philos[i++], NULL);
	pthread_join(monitor, NULL);
}

void	destroy_mutexes(t_rules *rules, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&rules->dead_lock);
	pthread_mutex_destroy(&rules->meal_lock);
}
