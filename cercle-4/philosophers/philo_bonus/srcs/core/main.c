/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 09:46:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	parse_rules(&rules, av);
	if (rules.nb_philo < 1 || rules.nb_philo > MAX_PHILOS)
	{
		ft_putstr_fd("Error: Wrong number of philosophers\n", 2);
		return (1);
	}
	philo(&rules);
	return (0);
}
