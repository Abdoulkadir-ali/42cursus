/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 04:59:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Check if a philosopher has died based on time since last meal.
 * @param philo Pointer to the philosopher struct.
 * @return 1 if the philosopher died, 0 otherwise.
 *
 * Locks meal_lock, prints status if dead, and unlocks. Used by monitor.
 */
static int	died(t_philo *philo)
{
	t_rules	*r;

	r = philo->rules;
	pthread_mutex_lock(&r->meal_lock);
	if (r->nb_meals != (size_t)-1 && philo->meals_eaten >= r->nb_meals)
	{
		pthread_mutex_unlock(&r->meal_lock);
		return (0);
	}
	if (now() - philo->last_meal >= r->time_to_die)
	{
		print_status(philo, "died");
		pthread_mutex_unlock(&r->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&r->meal_lock);
	return (0);
}

/**
 * @brief Check if all philosophers have finished their meals.
 * @param philos Array of philosopher structs.
 * @return 1 if all finished, 0 otherwise.
 *
 * Locks meal_lock for each philosopher, updates dead_flag if all finished.
 */
static int	check_meals(t_philo *philos)
{
	size_t	i;
	size_t	finished;
	t_rules	*r;

	r = philos[0].rules;
	if (r->nb_meals == (size_t)-1)
		return (0);
	i = 0;
	finished = 0;
	while (i < r->nb_philo)
	{
		pthread_mutex_lock(&r->meal_lock);
		if (philos[i].meals_eaten >= r->nb_meals)
			finished++;
		pthread_mutex_unlock(&r->meal_lock);
		i++;
	}
	if (finished == r->nb_philo)
	{
		pthread_mutex_lock(&r->dead_lock);
		r->dead_flag = 1;
		pthread_mutex_unlock(&r->dead_lock);
		return (1);
	}
	return (0);
}

/**
 * @brief Check if any philosopher has died or all have finished meals.
 * @param philos Array of philosopher structs.
 * @return 1 if any died or all finished, 0 otherwise.
 *
 * Calls died for each philosopher and check_meals for completion.
 */
static int	check_all_philos(t_philo *philos)
{
	size_t	i;
	t_rules	*r;

	r = philos[0].rules;
	i = 0;
	while (i < r->nb_philo)
	{
		if (died(&philos[i]))
			return (1);
		i++;
	}
	return (check_meals(philos));
}

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dead_lock);
	if (philo->rules->dead_flag)
	{
		pthread_mutex_unlock(&philo->rules->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->dead_lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_all_philos(philos))
			return (NULL);
		if (check_dead_flag(&philos[0]))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
