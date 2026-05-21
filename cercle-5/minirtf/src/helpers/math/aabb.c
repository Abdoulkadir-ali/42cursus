/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:44:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	aabb_reset(t_aabb *b)
{
	b->min = v3(1e30f, 1e30f, 1e30f);
	b->max = v3(-1e30f, -1e30f, -1e30f);
}

void	aabb_expand(t_aabb *b, t_vec3 p)
{
	if (p.x < b->min.x)
		b->min.x = p.x;
	if (p.y < b->min.y)
		b->min.y = p.y;
	if (p.z < b->min.z)
		b->min.z = p.z;
	if (p.x > b->max.x)
		b->max.x = p.x;
	if (p.y > b->max.y)
		b->max.y = p.y;
	if (p.z > b->max.z)
		b->max.z = p.z;
}

void	aabb_union(t_aabb *b, const t_aabb *o)
{
	if (o->min.x < b->min.x)
		b->min.x = o->min.x;
	if (o->min.y < b->min.y)
		b->min.y = o->min.y;
	if (o->min.z < b->min.z)
		b->min.z = o->min.z;
	if (o->max.x > b->max.x)
		b->max.x = o->max.x;
	if (o->max.y > b->max.y)
		b->max.y = o->max.y;
	if (o->max.z > b->max.z)
		b->max.z = o->max.z;
}

float	aabb_area(const t_aabb *b)
{
	t_vec3	d;

	d = v3_sub(b->max, b->min);
	if (d.x < 0 || d.y < 0 || d.z < 0)
		return (0.0f);
	return (2.0f * (d.x * d.y + d.y * d.z + d.z * d.x));
}

/* Branchless slab test using precomputed inv_d. */
int	aabb_hit(const t_aabb *b, const t_ray *r, const t_vec3 inv_d, float t_max)
{
	float	t[4];

	t[2] = (b->min.x - r->o.x) * inv_d.x;
	t[3] = (b->max.x - r->o.x) * inv_d.x;
	t[0] = fminf(t[2], t[3]);
	t[1] = fmaxf(t[2], t[3]);
	t[2] = (b->min.y - r->o.y) * inv_d.y;
	t[3] = (b->max.y - r->o.y) * inv_d.y;
	t[0] = fmaxf(t[0], fminf(t[2], t[3]));
	t[1] = fminf(t[1], fmaxf(t[2], t[3]));
	t[2] = (b->min.z - r->o.z) * inv_d.z;
	t[3] = (b->max.z - r->o.z) * inv_d.z;
	t[0] = fmaxf(t[0], fminf(t[2], t[3]));
	t[1] = fminf(t[1], fmaxf(t[2], t[3]));
	return (t[1] >= fmaxf(t[0], 0.0f) && t[0] < t_max);
}
