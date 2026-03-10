/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 04:54:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Entry point for the philosopher simulation.
 * @param ac Argument count (should be 5 or 6).
 * @param av Argument vector (simulation parameters).
 * @return 0 on success,
	1 on error (invalid arguments or too many philosophers).
 *
 * Validates arguments, parses rules, and launches the simulation.
 */
int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 1);
		return (1);
	}
	if (parse_rules(&rules, av))
	{
		ft_putstr_fd("Error: Invalid arguments\n", 1);
		return (1);
	}
	if (rules.nb_philo > MAX_PHILOS)
		return (1);
	philo(&rules);
	return (0);
}
