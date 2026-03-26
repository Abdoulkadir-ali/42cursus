/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Unified narrow phase: GJK -> EPA.
 * Runs collision detection and extraction of contact parameters.
 * @return 1 on collision, 0 otherwise.
 */
int	gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
		t_physics_body *ba, t_physics_body *bb,
		t_transform *ta, t_transform *tb,
		t_contact *c)
{
	t_simplex	simplex;
	t_epa_res	res;

	if (!gjk_intersect(sa, sb, &simplex))
		return (0);
	if (!gjk_epa(sa, sb, &simplex, &res))
		return (0);
	if (res.depth < 1e-9)
		return (0);
	c->normal = res.normal;
	c->penetration = res.depth;
	c->a = ba;
	c->b = bb;
	c->ta = ta;
	c->tb = tb;
	c->contact_point = vec3_scale(vec3_add(res.contact_a, res.contact_b), 0.5);
	c->ra = vec3_sub(c->contact_point, ba->center);
	c->rb = vec3_sub(c->contact_point, (bb ? bb->center : c->contact_point));
	c->restitution = fmin(ba->elasticity, bb ? bb->elasticity : 0.5);
	c->friction = sqrt(ba->friction * (bb ? bb->friction : 0.5));
	return (1);
}
