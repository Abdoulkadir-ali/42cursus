/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 01:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_aabb	aabb_create_empty(void)
{
	t_aabb	bbox;

	bbox.min = vec3(1e30, 1e30, 1e30);
	bbox.max = vec3(-1e30, -1e30, -1e30);
	return (bbox);
}

t_aabb	aabb_union(const t_aabb *a, const t_aabb *b)
{
	t_aabb	bbox;

	bbox.min = vec3(fmin(a->min.x, b->min.x), fmin(a->min.y, b->min.y),
			fmin(a->min.z, b->min.z));
	bbox.max = vec3(fmax(a->max.x, b->max.x), fmax(a->max.y, b->max.y),
			fmax(a->max.z, b->max.z));
	return (bbox);
}

void	aabb_expand_point(t_aabb *bbox, t_vec3 p)
{
	bbox->min.x = fmin(bbox->min.x, p.x);
	bbox->min.y = fmin(bbox->min.y, p.y);
	bbox->min.z = fmin(bbox->min.z, p.z);
	bbox->max.x = fmax(bbox->max.x, p.x);
	bbox->max.y = fmax(bbox->max.y, p.y);
	bbox->max.z = fmax(bbox->max.z, p.z);
}

void	aabb_expand_eps(t_aabb *bbox, double eps)
{
	bbox->min.x -= eps;
	bbox->min.y -= eps;
	bbox->min.z -= eps;
	bbox->max.x += eps;
	bbox->max.y += eps;
	bbox->max.z += eps;
}

double	aabb_surface_area(t_aabb bbox)
{
	t_vec3	d;

	d = vec3_sub(bbox.max, bbox.min);
	if (d.x < 0 || d.y < 0 || d.z < 0)
		return (0);
	return (2 * (d.x * d.y + d.y * d.z + d.z * d.x));
}

t_aabb	aabb_transform(t_aabb local, t_transform t)
{
	t_aabb	res;
	t_vec3	v[8];
	int		i;

	res = aabb_create_empty();
	v[0] = local.min;
	v[1] = vec3(local.min.x, local.min.y, local.max.z);
	v[2] = vec3(local.min.x, local.max.y, local.min.z);
	v[3] = vec3(local.min.x, local.max.y, local.max.z);
	v[4] = vec3(local.max.x, local.min.y, local.min.z);
	v[5] = vec3(local.max.x, local.min.y, local.max.z);
	v[6] = vec3(local.max.x, local.max.y, local.min.z);
	v[7] = local.max;
	i = -1;
	while (++i < 8)
		aabb_expand_point(&res, mat4_mul_pos(mat4_transform(t), v[i]));
	return (res);
}

bool	aabb_overlap(t_aabb a, t_aabb b)
{
	return ((a.min.x <= b.max.x && a.max.x >= b.min.x)
		&& (a.min.y <= b.max.y && a.max.y >= b.min.y)
		&& (a.min.z <= b.max.z && a.max.z >= b.min.z));
}
