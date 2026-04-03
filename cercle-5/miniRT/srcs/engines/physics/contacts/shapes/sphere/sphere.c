/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 10:52:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	set_sphere_contact(t_contact *c, t_sphere *sp,
				t_sphere *other, t_vec3 normal)
{
	c->normal = normal;
	c->penetration = (sqrt(sp->radius_sq) + sqrt(other->radius_sq))
		- vec3_mag(vec3_sub(sp->phys.pos, other->phys.pos));
	c->a = &sp->phys;
	c->b = &other->phys;
	c->ta = &sp->transform;
	c->tb = &other->transform;
	c->contact_point = vec3_add(sp->phys.pos, vec3_scale(normal,
				sqrt(sp->radius_sq) - c->penetration * 0.5));
	c->ra = vec3_sub(c->contact_point, sp->phys.pos);
	c->rb = vec3_sub(c->contact_point, other->phys.pos);
	c->restitution = fmin(sp->phys.elasticity, other->phys.elasticity);
	c->friction = sqrt(sp->phys.friction * other->phys.friction);
}

void	sphere_vs_sphere(t_sphere *sp, t_sphere *other, t_contact_query *q)
{
	t_vec3	d;
	t_vec3	n;
	double	dist_sq;
	double	r_sum;

	d = vec3_sub(sp->phys.pos, other->phys.pos);
	dist_sq = vec3_mag_sq(d);
	r_sum = sqrt(sp->radius_sq) + sqrt(other->radius_sq);
	if (dist_sq >= r_sum * r_sum || q->count >= q->max)
		return ;
	if (dist_sq > 1e-12)
		n = vec3_scale(d, -1.0 / sqrt(dist_sq));
	else
		n = vec3(0, 1, 0);
	set_sphere_contact(&q->contacts[q->count], sp, other, n);
	q->count++;
}
