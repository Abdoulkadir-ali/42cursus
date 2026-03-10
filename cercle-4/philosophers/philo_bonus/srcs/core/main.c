/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:06:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * main - Entry point for the philo_bonus simulation.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Validates argument count and values, parses rules, checks philosopher limit,
 * and launches the simulation. Prints errors to stderr on invalid input.
 * Returns 0 on success, 1 on error.
 */
int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	if (parse_rules(&rules, av))
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		return (1);
	}
	if (rules.nb_philo > MAX_PHILOS)
	{
		ft_putstr_fd("Error: Wrong number of philosophers\n", 2);
		return (1);
	}
	philo(&rules);
	return (0);
}
