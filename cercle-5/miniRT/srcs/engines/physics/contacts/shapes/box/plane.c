/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 11:42:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Sets contact information between a box corner and a plane.
 */
static void	set_box_contact(t_contact *c, t_box *bx, t_plane *pl, t_vec3 cor)
{
	c->normal = vec3_scale(vec3_norm(pl->transform.up), -1.0);
	c->penetration = -vec3_dot(vec3_sub(cor, pl->transform.pos),
			vec3_norm(pl->transform.up));
	c->a = &bx->phys;
	c->b = NULL;
	c->ta = &bx->transform;
	c->tb = &pl->transform;
	c->contact_point = cor;
	c->ra = vec3_sub(cor, bx->phys.pos);
	c->rb = vec3(0, 0, 0);
	c->restitution = fmin(bx->phys.elasticity, 0.5);
	c->friction = sqrt(bx->phys.friction * 0.5);
}

/**
 * @brief Computes the world-space position of a box corner.
 */
static t_vec3	get_box_cor(t_box *bx, size_t i, t_vec3 ax[3])
{
	t_vec3	he;
	t_vec3	s;

	he = bx->half_extents;
	s = vec3(-1.0, -1.0, -1.0);
	if (i & 1)
		s.x = 1.0;
	if (i & 2)
		s.y = 1.0;
	if (i & 4)
		s.z = 1.0;
	return (vec3_add(bx->phys.pos, vec3_add(vec3_add(
					vec3_scale(ax[0], s.x * he.x),
					vec3_scale(ax[1], s.y * he.y)),
				vec3_scale(ax[2], s.z * he.z))));
}

/**
 * @brief Tests a single box corner against a plane.
 * Uses the transform's actual oriented axes (right/up/forward) which are
 * kept current by integrate_box — avoids the vec3_orthonormal_basis
 * reconstruction that produced wrong corners after any rotation.
 */
static void	check_corner(t_contact_query *qu, t_box *bx, t_plane *pl, size_t i)
{
	t_vec3	ax[3];
	t_vec3	cor;

	ax[0] = bx->transform.forward;
	ax[1] = bx->transform.right;
	ax[2] = bx->transform.up;
	cor = get_box_cor(bx, i, ax);
	if (vec3_dot(vec3_sub(cor, pl->transform.pos),
			vec3_norm(pl->transform.up)) < 0.0 && qu->count < qu->max)
	{
		set_box_contact(&qu->contacts[qu->count], bx, pl, cor);
		qu->count++;
	}
}

/**
 * @brief Performs analytic contact generation for box vs all planes.
 */
size_t	box_vs_all_planes(t_contact_query *qu, t_box *bx)
{
	size_t	p;
	size_t	i;

	p = 0;
	while (p < qu->engine->scene->plane_count && qu->count < qu->max)
	{
		i = 0;
		while (i < 8 && qu->count < qu->max)
			check_corner(qu, bx, &qu->engine->scene->planes[p], i++);
		p++;
	}
	return (qu->count);
}
