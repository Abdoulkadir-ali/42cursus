/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:28:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:46:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_aabb	aabb_create_empty(void)
{
	t_aabb	aabb;

	aabb.min.x = MAX_VALUE;
	aabb.min.y = MAX_VALUE;
	aabb.min.z = MAX_VALUE;
	aabb.max.x = -MAX_VALUE;
	aabb.max.y = -MAX_VALUE;
	aabb.max.z = -MAX_VALUE;
	return (aabb);
}

void	aabb_expand_point(t_aabb *aabb, t_vec3 p)
{
	aabb->min.x = fmin(aabb->min.x, p.x);
	aabb->min.y = fmin(aabb->min.y, p.y);
	aabb->min.z = fmin(aabb->min.z, p.z);
	aabb->max.x = fmax(aabb->max.x, p.x);
	aabb->max.y = fmax(aabb->max.y, p.y);
	aabb->max.z = fmax(aabb->max.z, p.z);
}

t_aabb	aabb_union(const t_aabb *a, const t_aabb *b)
{
	t_aabb	res;

	res.min.x = fmin(a->min.x, b->min.x);
	res.min.y = fmin(a->min.y, b->min.y);
	res.min.z = fmin(a->min.z, b->min.z);
	res.max.x = fmax(a->max.x, b->max.x);
	res.max.y = fmax(a->max.y, b->max.y);
	res.max.z = fmax(a->max.z, b->max.z);
	return (res);
}

void	aabb_expand_eps(t_aabb *aabb, double eps)
{
	aabb->min.x -= eps;
	aabb->min.y -= eps;
	aabb->min.z -= eps;
	aabb->max.x += eps;
	aabb->max.y += eps;
	aabb->max.z += eps;
}

double	aabb_surface_area(const t_aabb *aabb)
{
	double	dx;
	double	dy;
	double	dz;

	dx = aabb->max.x - aabb->min.x;
	dy = aabb->max.y - aabb->min.y;
	dz = aabb->max.z - aabb->min.z;
	return (2.0 * (dx * dy + dy * dz + dz * dx));
}

bool	aabb_overlap(const t_aabb *a, const t_aabb *b)
{
	if (a->max.x < b->min.x || a->min.x > b->max.x)
		return (false);
	if (a->max.y < b->min.y || a->min.y > b->max.y)
		return (false);
	if (a->max.z < b->min.z || a->min.z > b->max.z)
		return (false);
	return (true);
}
