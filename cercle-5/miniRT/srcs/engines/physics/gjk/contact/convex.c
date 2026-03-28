/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Unified narrow phase: GJK -> EPA.
 * Runs collision detection and extraction of contact parameters.
 * @return 1 on collision, 0 otherwise.
 */
int	gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
		int idx_a, int idx_b,
		t_contact *c)
{
	t_simplex			simplex;
	t_epa_res			res;
	t_primitive_array	*p;
	t_physics_soa		*soa;
	int					pa;
	int					pb;

	if (!gjk_intersect(sa, sb, &simplex))
		return (0);
	if (!gjk_epa(sa, sb, &simplex, &res))
		return (0);
	if (res.depth < 1e-9)
		return (0);
	p = &sa->scene->primitives;
	soa = sa->scene->physics->soa;
	pa = p->phys_idx[idx_a];
	pb = p->phys_idx[idx_b];
	c->normal = res.normal;
	c->penetration = res.depth;
	c->idx_a = idx_a;
	c->idx_b = idx_b;
	c->contact_point = vec3_scale(vec3_add(res.contact_a, res.contact_b), 0.5);
	c->ra = vec3_sub(c->contact_point, vec3(p->px[idx_a], p->py[idx_a], p->pz[idx_a]));
	c->rb = vec3_sub(c->contact_point, vec3(p->px[idx_b], p->py[idx_b], p->pz[idx_b]));
	c->restitution = fmin((pa >= 0) ? soa->elasticity[pa] : 0.5,
			(pb >= 0) ? soa->elasticity[pb] : 0.5);
	c->friction = sqrt(((pa >= 0) ? soa->friction[pa] : 0.5) *
			((pb >= 0) ? soa->friction[pb] : 0.5));
	return (1);
}
