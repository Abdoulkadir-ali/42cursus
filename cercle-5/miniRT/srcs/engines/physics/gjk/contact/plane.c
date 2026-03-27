/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Handles plane vs. convex shape collision using support mapping.
 */
int	gjk_vs_plane(t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
		t_plane *pl, t_contact *c)
{
	t_vec3	n;
	t_vec3	support;
	double	dist;

	n = (vec3_mag_sq(pl->transform.up) < 1e-6) ? vec3(0, 1, 0)
		: vec3_norm(pl->transform.up);
	support = sa->support(sa->data, vec3_scale(n, -1.0));
	dist = vec3_dot(vec3_sub(support, pl->transform.pos), n);
	if (dist >= 0.0)
		return (0);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -dist;
	c->a = ba;
	c->b = NULL;
	c->ta = ta;
	c->tb = &pl->transform;
	c->contact_point = support;
	c->ra = vec3_sub(support, ba->center);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(ba->elasticity, 0.5);
	c->friction = sqrt(ba->friction * 0.5);
	return (1);
}
