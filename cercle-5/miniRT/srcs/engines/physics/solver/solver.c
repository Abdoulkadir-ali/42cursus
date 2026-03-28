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
 * @brief Dispatcher for solving position constraints (Baumgarte).
 * Iterates through all contacts and resolves overlaps.
 */
void	solve_positions(t_contact *c, int count)
{
	int				i;
	double			inv_a;
	double			inv_b;
	t_physics_soa	*s;
	int				pa, pb;

	if (count <= 0)
		return ;
	s = c[0].scene->physics->soa;
	i = 0;
	while (i < count)
	{
		pa = c[i].scene->primitives.phys_idx[c[i].idx_a];
		pb = c[i].scene->primitives.phys_idx[c[i].idx_b];
		inv_a = (pa >= 0) ? s->inv_mass[pa] : 0.0;
		inv_b = (pb >= 0) ? s->inv_mass[pb] : 0.0;
		if (inv_a + inv_b > 1e-8)
			apply_position_correction(&c[i], inv_a, inv_b);
		i++;
	}
}
