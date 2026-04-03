/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 10:52:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	set_sphere_plane_contact(t_contact *c, t_sphere *sp,
				t_plane *pl, t_vec3 n)
{
	double	r;
	double	dist;

	r = sqrt(sp->radius_sq);
	dist = vec3_dot(vec3_sub(sp->phys.pos, pl->transform.pos), n);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = r - dist;
	c->a = &sp->phys;
	c->ta = &sp->transform;
	c->b = NULL;
	c->tb = &pl->transform;
	c->contact_point = vec3_sub(sp->phys.pos, vec3_scale(n, r));
	c->ra = vec3_scale(n, -r);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(sp->phys.elasticity, 0.5);
	c->friction = sqrt(sp->phys.friction * 0.5);
}

void	sphere_vs_plane_analytic(t_sphere *sp, t_plane *pl, t_contact_query *q)
{
	t_vec3	n;
	t_vec2	d;

	n = vec3_norm(pl->transform.up);
	d.x = vec3_dot(vec3_sub(sp->phys.pos, pl->transform.pos), n);
	d.y = sqrt(sp->radius_sq);
	if (d.x >= d.y || q->count >= q->max)
		return ;
	set_sphere_plane_contact(&q->contacts[q->count], sp, pl, n);
	q->count++;
}
