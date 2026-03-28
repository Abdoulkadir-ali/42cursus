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

	sa = (t_gjk_shape){phys->scene, idx_a};
	sb = (t_gjk_shape){phys->scene, idx_b};
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
	c->ra = vec3_sub(c->contact_point, vec3(phys->soa.px[idx_a],
				phys->soa.py[idx_a], phys->soa.pz[idx_a]));
	c->rb = vec3_sub(c->contact_point, vec3(phys->soa.px[idx_b],
				phys->soa.py[idx_b], phys->soa.pz[idx_b]));
	c->restitution = fmin(phys->soa.restitution[idx_a],
			phys->soa.restitution[idx_b]);
	c->friction = sqrt(phys->soa.friction[idx_a] * phys->soa.friction[idx_b]);
	return (1);
}

int	gjk_vs_plane(t_physics *phys, int body_idx, int plane_idx, t_contact *c)
{
	t_vec3		n;
	t_vec3		support;
	double		dist;
	t_gjk_shape	sa;

	sa = (t_gjk_shape){phys->scene, body_idx};
	n = vec3_norm(vec3(phys->soa.ax[plane_idx], phys->soa.ay[plane_idx],
				phys->soa.az[plane_idx]));
	support = sa_support(&sa, vec3_scale(n, -1.0));
	dist = vec3_dot(vec3_sub(support, vec3(phys->soa.px[plane_idx],
					phys->soa.py[plane_idx], phys->soa.pz[plane_idx])), n);
	if (dist >= 0.0)
		return (0);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -dist;
	c->idx_a = body_idx;
	c->idx_b = plane_idx;
	c->contact_point = support;
	c->ra = vec3_sub(support, vec3(phys->soa.px[body_idx],
				phys->soa.py[body_idx], phys->soa.pz[body_idx]));
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(phys->soa.restitution[body_idx], 0.5);
	c->friction = sqrt(phys->soa.friction[body_idx] * 0.5);
	return (1);
}
