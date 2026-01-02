/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 13:31:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	print_death(t_philo *philo)
{
	philo->rules->dead_flag = 1;
	printf("%ld %zu died\n", now() - philo->sim_start, philo->id);
}

static int	died(t_philo *philo)
{
	t_rules	*r;

	r = philo->rules;
	pthread_mutex_lock(&r->meal_lock);
	if (now() - philo->last_meal >= r->time_to_die)
	{
		pthread_mutex_lock(&r->dead_lock);
		if (!r->dead_flag)
			print_death(philo);
		pthread_mutex_unlock(&r->dead_lock);
		pthread_mutex_unlock(&r->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&r->meal_lock);
	return (0);
}

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
