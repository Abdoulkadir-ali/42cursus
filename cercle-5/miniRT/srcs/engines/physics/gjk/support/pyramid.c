/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Precomputes the 5 world-space vertices of a pyramid.
 */
static void	get_pyramid_verts(const t_pyramid *py, t_vec3 *v)
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
	v[4] = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
}

/**
 * @brief Returns the furthest vertex of a pyramid along the search direction.
 */
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir)
{
	const t_pyramid	*py;
	t_vec3			verts[5];
	t_vec3			best;
	double			best_d;
	size_t			i;

	py = (const t_pyramid *)data;
	get_pyramid_verts(py, verts);
	best = verts[0];
	best_d = vec3_dot(verts[0], dir);
	i = 1;
	while (i < 5)
	{
		if (vec3_dot(verts[i], dir) > best_d)
		{
			best_d = vec3_dot(verts[i], dir);
			best = verts[i];
		}
		i++;
	}
	return (best);
}
