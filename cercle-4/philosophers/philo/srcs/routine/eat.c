/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 16:44:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	print_status(philo, "has taken a fork");
	if (philo->rules->nb_philo == 1)
	{
		precise_usleep(philo->rules->time_to_die);
		pthread_mutex_unlock(philo->left_f);
		return (1);
	}
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(philo->left_f);
		return (1);
	}
	pthread_mutex_lock(philo->right_f);
	print_status(philo, "has taken a fork");
	return (0);
}

static void	perform_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->meal_lock);
	philo->last_meal = now();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	print_status(philo, "is eating");
	precise_usleep(philo->rules->time_to_eat);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

int	philo_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	perform_eating(philo);
	drop_forks(philo);
	if (philo->rules->nb_meals != (size_t)-1
		&& philo->meals_eaten >= philo->rules->nb_meals)
		return (1);
	return (0);
}
