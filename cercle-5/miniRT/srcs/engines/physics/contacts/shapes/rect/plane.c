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

static void	set_rect_plane_contact(t_contact *c, t_rect *rc,
					t_plane *pl, size_t i)
{
	t_vec3	n;
	t_vec3	to_v;

	n = vec3_norm(pl->transform.up);
	to_v = vec3_sub(rc->v[i], pl->transform.pos);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -vec3_dot(to_v, n);
	c->a = &rc->phys;
	c->b = NULL;
	c->ta = &rc->transform;
	c->tb = &pl->transform;
	c->contact_point = rc->v[i];
	c->ra = vec3_sub(rc->v[i], rc->phys.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(rc->phys.elasticity, 0.5);
	c->friction = sqrt(rc->phys.friction * 0.5);
}

static void	check_rect_vert(t_contact_query *qu, t_rect *rc,
					t_plane *pl, size_t i)
{
	t_vec3	n;
	t_vec3	to_v;

	n = vec3_norm(pl->transform.up);
	to_v = vec3_sub(rc->v[i], pl->transform.pos);
	if (vec3_dot(to_v, n) < 0.0 && qu->count < qu->max)
	{
		set_rect_plane_contact(&qu->contacts[qu->count], rc, pl, i);
		qu->count++;
	}
}

size_t	rect_vs_all_planes(t_contact_query *qu, t_rect *rc)
{
	size_t	p;
	size_t	i;

	p = 0;
	while (p < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		i = 0;
		while (i < 4 && qu->count < qu->max)
		{
				check_rect_vert(qu, rc, &qu->engine->scene->planes[p], i);
			i++;
		}
		p++;
	}
	return (qu->count);
}
