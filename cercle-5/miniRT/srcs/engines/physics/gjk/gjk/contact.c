/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:09:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Unified narrow phase: GJK -> EPA.
 * Runs collision detection and extraction of contact parameters.
 * @return 1 on collision, 0 otherwise.
 */
int	gjk_make_contact(t_physics *phys, int idx_a, int idx_b, t_contact *c)
{
	t_simplex	simplex;
	t_epa_res	res;
	t_gjk_shape	sa;
	t_gjk_shape	sb;

	init_gjk_shape(&sa, phys, idx_a);
	init_gjk_shape(&sb, phys, idx_b);
	if (!gjk_intersect(&sa, &sb, &simplex))
		return (0);
	if (!gjk_epa(&sa, &sb, &simplex, &res))
		return (0);
	if (res.depth < 1e-9)
		return (0);
	c->normal = res.normal;
	c->penetration = res.depth;
	c->idx_a = idx_a;
	c->idx_b = idx_b;
	c->contact_point = vec3_scale(vec3_add(res.contact_a, res.contact_b), 0.5);
	c->ra = vec3_sub(c->contact_point, vec3(phys->scene->primitives.px[idx_a],
				phys->scene->primitives.py[idx_a], phys->scene->primitives.pz[idx_a]));
	c->rb = vec3_sub(c->contact_point, vec3(phys->scene->primitives.px[idx_b],
				phys->scene->primitives.py[idx_b], phys->scene->primitives.pz[idx_b]));
	int pa = phys->scene->primitives.phys_idx[idx_a];
	int pb = phys->scene->primitives.phys_idx[idx_b];
	if (pa != -1 && pb != -1)
	{
		c->restitution = fmin(phys->soa->elasticity[pa], phys->soa->elasticity[pb]);
		c->friction = sqrt(phys->soa->friction[pa] * phys->soa->friction[pb]);
	}
	else
	{
		c->restitution = 0.5;
		c->friction = 0.5;
	}
	return (1);
}

int	gjk_vs_plane(t_physics *phys, int body_idx, int plane_idx, t_contact *c)
{
	t_vec3		n;
	t_vec3		support;
	double		dist;
	t_gjk_shape	sa;

	init_gjk_shape(&sa, phys, body_idx);
	n = vec3_norm(vec3(phys->scene->primitives.ax[plane_idx], phys->scene->primitives.ay[plane_idx],
				phys->scene->primitives.az[plane_idx]));
	support = sa.support(&sa, vec3_scale(n, -1.0));
	dist = vec3_dot(vec3_sub(support, vec3(phys->scene->primitives.px[plane_idx],
					phys->scene->primitives.py[plane_idx], phys->scene->primitives.pz[plane_idx])), n);
	if (dist >= 0.0)
		return (0);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -dist;
	c->idx_a = body_idx;
	c->idx_b = plane_idx;
	c->contact_point = support;
	c->ra = vec3_sub(support, vec3(phys->scene->primitives.px[body_idx],
				phys->scene->primitives.py[body_idx], phys->scene->primitives.pz[body_idx]));
	c->rb = vec3(0, 0, 0);
	int pb = phys->scene->primitives.phys_idx[body_idx];
	if (pb != -1)
	{
		c->restitution = fmin(phys->soa->elasticity[pb], 0.5);
		c->friction = sqrt(phys->soa->friction[pb] * 0.5);
	}
	else
	{
		c->restitution = 0.5;
		c->friction = 0.5;
	}
	return (1);
}
