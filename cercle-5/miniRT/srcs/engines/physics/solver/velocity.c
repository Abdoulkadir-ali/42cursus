/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   velocity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:21:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Dispatcher for solving velocity constraints.
 * Iterates through all contacts and applies impulses.
 */
static void	apply_velocity_impulse(t_physics *phys, t_contact *c,
		t_physics_soa *s, int pa, int pb)
{
	double	inv_a;
	double	inv_b;
	double	j;

	inv_a = 0.0;
	if (pa >= 0)
		inv_a = s->inv_mass[pa];
	inv_b = 0.0;
	if (pb >= 0)
		inv_b = s->inv_mass[pb];
	if (inv_a + inv_b > 1e-8)
	{
		j = solve_one_velocity(phys, c, inv_a, inv_b);
		if (pa >= 0 && s->is_compound[pa])
			apply_torque(phys, c, pa, j);
		if (pb >= 0 && s->is_compound[pb])
			apply_torque(phys, c, pb, -j);
	}
}

void	solve_velocities(t_physics *phys, t_contact *c, int count)
{
	int				i;
	t_physics_soa	*s;

	if (count <= 0)
		return ;
	s = phys->soa;
	i = 0;
	while (i < count)
	{
		apply_velocity_impulse(phys, &c[i], s,
			phys->scene->primitives.phys_idx[c[i].idx_a],
			phys->scene->primitives.phys_idx[c[i].idx_b]);
		i++;
	}
}

