/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:35:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	set_tri_plane_contact(t_contact *c, t_tri_shape *tr,
					t_plane *pl, size_t i)
{
	t_vec3	n;
	t_vec3	to_v;

	n = vec3_norm(pl->transform.up);
	to_v = vec3_sub(tr->v[i], pl->transform.pos);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -vec3_dot(to_v, n);
	c->a = &tr->phys;
	c->b = NULL;
	c->ta = &tr->xform;
	c->tb = &pl->transform;
	c->contact_point = tr->v[i];
	c->ra = vec3_sub(tr->v[i], tr->phys.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(tr->phys.elasticity, 0.5);
	c->friction = sqrt(tr->phys.friction * 0.5);
}

static void	check_tri_vert(t_contact_query *qu, t_tri_shape *tr,
					t_plane *pl, size_t i)
{
	t_vec3	n;

	n = vec3_norm(pl->transform.up);
	if (vec3_dot(vec3_sub(tr->v[i], pl->transform.pos), n) < 0.0
		&& qu->count < qu->max)
	{
		set_tri_plane_contact(&qu->contacts[qu->count], tr, pl, i);
		qu->count++;
	}
}

size_t	tri_vs_all_planes(t_contact_query *qu, t_tri_shape *tr)
{
	size_t	p;
	size_t	i;

	p = 0;
	while (p < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		i = 0;
		while (i < 3 && qu->count < qu->max)
		{
			check_tri_vert(qu, tr, &qu->engine->scene->planes[p], i);
			i++;
		}
		p++;
	}
	return (qu->count);
}
