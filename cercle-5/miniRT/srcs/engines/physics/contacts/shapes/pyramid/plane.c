/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	set_py_plane_contact(t_contact *c, t_pyramid *py,
				t_plane *pl, t_vec3 v)
{
	t_vec3	n;

	n = vec3_norm(pl->transform.up);
	c->normal = vec3_scale(n, -1.0);
	c->penetration = -vec3_dot(vec3_sub(v, pl->transform.pos), n);
	c->a = &py->phys;
	c->b = NULL;
	c->ta = &py->transform;
	c->tb = &pl->transform;
	c->contact_point = v;
	c->ra = vec3_sub(v, py->phys.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(py->phys.elasticity, 0.5);
	c->friction = sqrt(py->phys.friction * 0.5);
}

static void	check_py_vert(t_contact_query *qu, t_pyramid *py,
				t_plane *pl, t_vec3 v)
{
	t_vec3	n;

	n = vec3_norm(pl->transform.up);
	if (vec3_dot(vec3_sub(v, pl->transform.pos), n) < 0.0
		&& qu->count < qu->max)
	{
		set_py_plane_contact(&qu->contacts[qu->count], py, pl, v);
		qu->count++;
	}
}

size_t	pyramid_vs_planes(t_contact_query *qu, t_pyramid *py)
{
	size_t	p;
	size_t	i;

	p = 0;
	while (p < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		i = 0;
		while (i < 4 && qu->count < qu->max)
		{
			check_py_vert(qu, py, &qu->engine->scene->planes[p], py->c[i]);
			i++;
		}
		if (qu->count < qu->max)
			check_py_vert(qu, py, &qu->engine->scene->planes[p], py->apex);
		p++;
	}
	return (qu->count);
}
