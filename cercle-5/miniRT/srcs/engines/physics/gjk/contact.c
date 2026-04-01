/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:51:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** gjk_make_contact — unified narrow phase.
**
** Given two GJK shapes with their physics bodies and transforms,
** runs GJK → EPA and fills a t_contact.  Returns 1 on collision, 0 otherwise.
**
** The collision normal always points from shape A toward shape B (the solver
** convention used throughout the codebase).
**
** Plane vs. shape is handled separately (gjk_vs_plane) because a half-space
** is not convex in the GJK sense — its support function is degenerate.
*/

int	gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
		t_physics_body *ba, t_physics_body *bb,
		t_transform *ta, t_transform *tb,
		t_contact *c)
{
	t_simplex	simplex;
	t_vec3		normal;
	t_vec3		contact_a;
	t_vec3		contact_b;
	t_vec3		contact_pt;
	double		depth;

	if (!gjk_intersect(sa, sb, &simplex))
		return (0);
	if (!gjk_epa(sa, sb, &simplex, &normal, &depth,
			&contact_a, &contact_b))
		return (0);
	if (depth < 1e-9)
		return (0);
	contact_pt = vec3_scale(vec3_add(contact_a, contact_b), 0.5);
	c->normal = normal;
	c->penetration = depth;
	c->a = ba;
	c->b = bb;
	c->ta = ta;
	c->tb = tb;
	c->contact_point = contact_pt;
	c->ra = vec3_sub(contact_pt, ba->center);
	c->rb = vec3_sub(contact_pt, (bb ? bb->center : contact_pt));
	c->restitution = fmin(ba->elasticity, bb ? bb->elasticity : 0.5);
	c->friction = sqrt(ba->friction * (bb ? bb->friction : 0.5));
	return (1);
}

/*
** gjk_vs_plane — shape A (any convex) vs. plane.
**
** The plane-vs-shape test is the signed-distance of the support point
** in -normal direction.  This correctly handles any convex A.
** Returns number of contacts written into c[] (0 or 1).
*/
int	gjk_vs_plane(t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
		t_plane *pl, t_contact *c)
{
	t_vec3	n;
	t_vec3	support;
	t_vec3	to_support;
	double	dist;

	if (vec3_mag_sq(pl->transform.up) < 1e-6)
		n = vec3(0, 1, 0);
	else
		n = vec3_norm(pl->transform.up);
	support = sa->support(sa->data, vec3_scale(n, -1.0));
	to_support = vec3_sub(support, pl->transform.pos);
	dist = vec3_dot(to_support, n);
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
