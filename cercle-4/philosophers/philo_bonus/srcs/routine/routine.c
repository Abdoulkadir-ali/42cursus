/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 09:25:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 13:43:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_rules *r)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/meal_check");
	sem_unlink("/waiter");
	r->forks = sem_open("/forks", O_CREAT, 0644, r->nb_philo);
	r->print = sem_open("/print", O_CREAT, 0644, 1);
	r->stop = sem_open("/stop", O_CREAT, 0644, 0);
	r->meal_check = sem_open("/meal_check", O_CREAT, 0644, 0);
	r->waiter = sem_open("/waiter", O_CREAT, 0644, r->nb_philo - 1);
}

void	start_simulation(t_rules *rules, t_philo *philos)
{
	size_t	i;
	long	start;

	i = 0;
	start = now();
	while (i < rules->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].sim_start = start;
		philos[i].rules = rules;
		philos[i].last_meal = start;
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			philo_routine(&philos[i]);
			exit(0);
		}
		i++;
	}
}

void	terminate_simulation(t_rules *rules, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < rules->nb_philo)
		kill(philos[i++].pid, SIGKILL);
	i = 0;
	while (i < rules->nb_philo)
		waitpid(philos[i++].pid, NULL, 0);
	sem_close(rules->forks);
	sem_close(rules->print);
	sem_close(rules->waiter);
	sem_close(rules->stop);
	sem_close(rules->meal_check);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/meal_check");
	sem_unlink("/waiter");
}

void	philo_routine(t_philo *p)
{
	pthread_t	monitor;

	sem_init(&p->meal_lock, 0, 1);
	p->last_meal = now();
	pthread_create(&monitor, NULL, death_monitor, p);
	pthread_detach(monitor);
	if (p->id % 2 == 0)
		precise_usleep(p->rules->time_to_eat / 2);
	while (1)
	{
		philo_eat(p);
		philo_sleep(p);
		philo_think(p);
	}
}

void	philo(t_rules *rules)
{
	t_philo		philos[MAX_PHILOS];
	pthread_t	meal_check_thread;

	init_semaphores(rules);
	start_simulation(rules, philos);
	if (rules->nb_meals != (size_t)-1)
	{
		pthread_create(&meal_check_thread, NULL, meal_monitor, rules);
		pthread_detach(meal_check_thread);
	}
	sem_wait(rules->stop);
	terminate_simulation(rules, philos);
}
