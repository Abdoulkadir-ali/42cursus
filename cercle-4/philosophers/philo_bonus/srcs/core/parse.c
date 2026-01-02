/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 11:29:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_rules(t_rules *rules, char **av)
{
	long long	nb_philo;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	nb_meals;

	nb_philo = ft_atoll(av[1]);
	time_to_die = ft_atoll(av[2]);
	time_to_eat = ft_atoll(av[3]);
	time_to_sleep = ft_atoll(av[4]);
	if (nb_philo <= 0 || time_to_die <= 0
		|| time_to_eat <= 0 || time_to_sleep <= 0)
		return (1);
	rules->nb_philo = (size_t)nb_philo;
	rules->time_to_die = (size_t)time_to_die;
	rules->time_to_eat = (size_t)time_to_eat;
	rules->time_to_sleep = (size_t)time_to_sleep;
	if (av[5])
	{
		nb_meals = ft_atoll(av[5]);
		if (nb_meals <= 0)
			return (1);
		rules->nb_meals = (size_t)nb_meals;
	}
	else
		rules->nb_meals = -1;
	return (0);
}
