/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "physics.h"
#include "scene.h"

bool	collide_sphere_sphere(t_sphere *a, t_sphere *b, t_contact *c)
{
	t_vec3	delta;
	double	dist_sq;
	double	r_sum;
	double	dist;

	delta = vec3_sub(b->transform.pos, a->transform.pos);
	dist_sq = vec3_mag_sq(delta);
	r_sum = sqrt(a->radius_sq) + sqrt(b->radius_sq);
	if (dist_sq > r_sum * r_sum || dist_sq < 1e-8)
		return (false);
	dist = sqrt(dist_sq);
	c->normal = vec3_scale(delta, 1.0 / dist);
	c->penetration = r_sum - dist;
	c->a = &a->phys;
	c->b = &b->phys;
	c->ta = &a->transform;
	c->tb = &b->transform;
	c->contact_point = vec3_add(a->transform.pos,
			vec3_scale(c->normal, sqrt(a->radius_sq)));
	c->ra = vec3_sub(c->contact_point, a->transform.pos);
	c->rb = vec3_sub(c->contact_point, b->transform.pos);
	c->restitution = fmin(a->phys.elasticity, b->phys.elasticity);
	c->friction = sqrt(a->phys.friction * b->phys.friction);
	return (true);
}

bool	collide_sphere_plane(t_sphere *s, t_plane *pl, t_contact *c)
{
	t_vec3	normal;
	t_vec3	to_center;
	double	dist;
	double	radius;

	normal = pl->transform.up;
	if (vec3_mag_sq(normal) < 1e-6)
		normal = (t_vec3){0, 1, 0, 0};
	else
		normal = vec3_norm(normal);
	to_center = vec3_sub(s->transform.pos, pl->transform.pos);
	dist = vec3_dot(to_center, normal);
	radius = sqrt(s->radius_sq);
	if (dist >= radius)
		return (false);
	c->normal = vec3_scale(normal, -1.0);
	c->penetration = radius - dist;
	c->a = &s->phys;
	c->b = NULL;
	c->ta = &s->transform;
	c->tb = &pl->transform;
	c->contact_point = vec3_sub(s->transform.pos,
			vec3_scale(normal, radius));
	c->ra = vec3_sub(c->contact_point, s->transform.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(s->phys.elasticity, 0.5);
	c->friction = sqrt(s->phys.friction * 0.5);
	return (true);
}

bool	collide_sphere_mesh(t_sphere *s, t_mesh *m, t_contact *c)
{
	t_vec3	n;
	double	pen;

	if (!detect_sphere_mesh_collision(s, m, &n, &pen))
		return (false);
	c->normal = n;
	c->penetration = pen;
	c->a = &s->phys;
	c->b = NULL;
	c->ta = &s->transform;
	c->tb = &m->transform;
	c->contact_point = vec3_sub(s->transform.pos,
			vec3_scale(n, sqrt(s->radius_sq)));
	c->ra = vec3_sub(c->contact_point, s->transform.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = s->phys.elasticity;
	c->friction = sqrt(s->phys.friction * m->phys.friction);
	return (true);
}
