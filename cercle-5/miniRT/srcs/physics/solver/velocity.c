/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:36:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Dispatcher for solving velocity constraints.
 * Iterates through all contacts and applies impulses.
 */
void	solve_velocities(t_contact *c, int count)
{
	int		i;
	double	inv_a;
	double	inv_b;

	i = 0;
	while (i < count)
	{
		inv_a = get_inv_mass(c[i].a);
		inv_b = get_inv_mass(c[i].b);
		if (inv_a + inv_b > 1e-8)
			solve_one_velocity(&c[i], inv_a, inv_b);
		i++;
	}
}
