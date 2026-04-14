/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   velocity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:41:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Top-level velocity solver loop. Resolves impulses for all contacts.
 * Iterates through the contact list and applies sequential impulses.
 */
void	solve_velocities(t_contact *c, t_physic_engine *en, size_t count)
{
	size_t	i;
	double	ia;
	double	ib;

	i = 0;
	while (i < count)
	{
		ia = get_inv_mass(c[i].a);
		ib = get_inv_mass(c[i].b);
		if ((ia < 1e-15 && c[i].a && !c[i].a->is_static)
			|| (ib < 1e-15 && c[i].b && !c[i].b->is_static))
		{
			i++;
			continue ;
		}
		if (ia + ib > 1e-15)
			solve_one_velocity(&c[i], en, ia, ib);
		i++;
	}
}
