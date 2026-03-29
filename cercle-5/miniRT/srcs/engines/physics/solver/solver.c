/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:33:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static bool	check_indices(t_physics *phys, t_contact *c)
{
	if (c->idx_a < 0 || (size_t)c->idx_a >= phys->scene->primitives.count
		|| c->idx_b < 0 || (size_t)c->idx_b >= phys->scene->primitives.count)
		return (false);
	if (phys->scene->primitives.phys_idx[c->idx_a] < 0
		|| (size_t)phys->scene->primitives.phys_idx[c->idx_a] >= phys->soa->count
		|| phys->scene->primitives.phys_idx[c->idx_b] < 0
		|| (size_t)phys->scene->primitives.phys_idx[c->idx_b] >= phys->soa->count)
		return (false);
	return (true);
}

static void	apply_pos_impulse(t_physics *phys, t_contact *c, t_physics_soa *s)
{
	double	inv_a;
	double	inv_b;
	int		pa;
	int		pb;

	pa = phys->scene->primitives.phys_idx[c->idx_a];
	pb = phys->scene->primitives.phys_idx[c->idx_b];
	inv_a = 0.0;
	if (pa >= 0)
		inv_a = s->inv_mass[pa];
	inv_b = 0.0;
	if (pb >= 0)
		inv_b = s->inv_mass[pb];
	if (inv_a + inv_b > 1e-8)
		apply_position_correction(phys, c, inv_a, inv_b);
}

void	solve_positions(t_physics *phys, t_contact *c, int count)
{
	int				i;
	t_physics_soa	*s;

	if (count <= 0)
		return ;
	s = phys->soa;
	i = -1;
	while (++i < count)
	{
		if (check_indices(phys, &c[i]))
			apply_pos_impulse(phys, &c[i], s);
	}
}
