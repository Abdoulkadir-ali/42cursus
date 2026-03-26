/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Sets the 8 corners of the AABB.
 */
static void	set_corners(t_vec3 c[8], t_aabb local)
{
	c[0] = local.min;
	c[1] = vec3(local.min.x, local.min.y, local.max.z);
	c[2] = vec3(local.min.x, local.max.y, local.min.z);
	c[3] = vec3(local.min.x, local.max.y, local.max.z);
	c[4] = vec3(local.max.x, local.min.y, local.min.z);
	c[5] = vec3(local.max.x, local.min.y, local.max.z);
	c[6] = vec3(local.max.x, local.max.y, local.min.z);
	c[7] = local.max;
}

/**
 * Transforms a local AABB into world space by applying the object's transform.
 * Handles translation, rotation, and scaling.
 */
t_aabb	aabb_transform(t_aabb local, t_transform t)
{
	t_aabb	w;
	t_vec3	c[8];
	t_mat4	m;
	t_vec3	v;
	int		i;

	m = mat4_transform(t);
	set_corners(c, local);
	w.min = vec3(MAX_VALUE, MAX_VALUE, MAX_VALUE);
	w.max = vec3(-MAX_VALUE, -MAX_VALUE, -MAX_VALUE);
	i = 0;
	while (i < 8)
	{
		v = mat4_mul_pos(m, c[i]);
		w.min.x = fmin(w.min.x, v.x);
		w.min.y = fmin(w.min.y, v.y);
		w.min.z = fmin(w.min.z, v.z);
		w.max.x = fmax(w.max.x, v.x);
		w.max.y = fmax(w.max.y, v.y);
		w.max.z = fmax(w.max.z, v.z);
		i++;
	}
	return (w);
}
