/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:24:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	pyramid_verts(t_pyramid *py, t_vec3 v[5])
{
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	double	h;

	h = py->base_size * 0.5;
	ref = vec3(0, 1, 0);
	if (fabs(py->up.y) >= 0.9)
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	v[0] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, h)), vec3_scale(fwd, h));
	v[1] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, -h)), vec3_scale(fwd, h));
	v[2] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, -h)), vec3_scale(fwd, -h));
	v[3] = vec3_add(vec3_add(py->transform.pos,
				vec3_scale(right, h)), vec3_scale(fwd, -h));
	v[4] = vec3_add(py->transform.pos,
			vec3_scale(py->up, py->height));
}

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
	t_vec3	v[5];
	size_t	p;
	size_t	i;

	pyramid_verts(py, v);
	p = 0;
	while (p < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		i = 0;
		while (i < 5 && qu->count < qu->max)
		{
			check_py_vert(qu, py, &qu->engine->scene->planes[p], v[i]);
			i++;
		}
		p++;
	}
	return (qu->count);
}
