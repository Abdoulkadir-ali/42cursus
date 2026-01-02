/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 11:32:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*meal_monitor(void *arg)
{
	t_rules	*rules;
	size_t	i;

	rules = (t_rules *)arg;
	i = 0;
	while (i < rules->nb_philo)
	{
		sem_wait(rules->meal_check);
		i++;
	}
	sem_post(rules->stop);
	return (NULL);
}

static void	handle_one_philo(t_philo *p)
{
	sem_wait(p->rules->forks);
	print_status(p, "has taken a fork");
	while (1)
		precise_usleep(1000);
}

static void	take_forks(t_philo *p)
{
	if (p->rules->nb_philo > 1)
		sem_wait(p->rules->waiter);
	sem_wait(p->rules->forks);
	print_status(p, "has taken a fork");
	sem_wait(p->rules->forks);
	print_status(p, "has taken a fork");
}

static void	drop_forks(t_philo *p)
{
	sem_post(p->rules->forks);
	sem_post(p->rules->forks);
	if (p->rules->nb_philo > 1)
		sem_post(p->rules->waiter);
}

void	philo_eat(t_philo *p)
{
	if (p->rules->nb_philo == 1)
	{
		handle_one_philo(p);
		return ;
	}
	take_forks(p);
	print_status(p, "is eating");
	sem_wait(&p->meal_lock);
	p->last_meal = now();
	sem_post(&p->meal_lock);
	p->meals_eaten++;
	if (p->rules->nb_meals != (size_t)-1 && p->meals_eaten == p->rules->nb_meals)
		sem_post(p->rules->meal_check);
	precise_usleep(p->rules->time_to_eat);
	drop_forks(p);
}
