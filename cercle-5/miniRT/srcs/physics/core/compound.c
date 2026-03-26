/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_aabb	aabb_union(t_aabb a, t_aabb b)
{
	t_aabb	r;

	r.min.x = fmin(a.min.x, b.min.x);
	r.min.y = fmin(a.min.y, b.min.y);
	r.min.z = fmin(a.min.z, b.min.z);
	r.max.x = fmax(a.max.x, b.max.x);
	r.max.y = fmax(a.max.y, b.max.y);
	r.max.z = fmax(a.max.z, b.max.z);
	return (r);
}

static void	compute_com(t_physics_body *b)
{
	size_t	i;
	t_vec3	sum;

	sum = vec3(0, 0, 0);
	i = 0;
	while (i < b->sub_count)
	{
		sum = vec3_add(sum, b->sub_shapes[i].offset);
		i++;
	}
	if (b->sub_count > 0)
		b->com = vec3_scale(sum, 1.0 / (double)b->sub_count);
	else
		b->com = vec3(0, 0, 0);
}

/**
 * @brief Computes global_aabb from current sub-shape world positions.
 * Call each frame after position integration.
 */
static void	compute_inertia(t_physics_body *b)
{
	size_t	i;
	t_vec3	r;
	double	m_sub;

	memset(&b->inv_inertia, 0, sizeof(t_mat3));
	if (b->mass < 1e-6) return ;
	m_sub = b->mass / (double)b->sub_count;
	i = 0;
	while (i < b->sub_count)
	{
		r = vec3_sub(b->sub_shapes[i].offset, b->com);
		b->inv_inertia.m[0][0] += m_sub * (r.y * r.y + r.z * r.z);
		b->inv_inertia.m[1][1] += m_sub * (r.x * r.x + r.z * r.z);
		b->inv_inertia.m[2][2] += m_sub * (r.x * r.x + r.y * r.y);
		b->inv_inertia.m[0][1] -= m_sub * (r.x * r.y);
		b->inv_inertia.m[0][2] -= m_sub * (r.x * r.z);
		b->inv_inertia.m[1][2] -= m_sub * (r.y * r.z);
		i++;
	}
	b->inv_inertia.m[1][0] = b->inv_inertia.m[0][1];
	b->inv_inertia.m[2][0] = b->inv_inertia.m[0][2];
	b->inv_inertia.m[2][1] = b->inv_inertia.m[1][2];
	b->inv_inertia = mat3_inv(b->inv_inertia);
}

void	update_compound(t_physics_body *b)
{
	size_t	i;
	t_aabb	acc;

	if (!b->is_compound || b->sub_count == 0)
		return ;
	acc = b->sub_shapes[0].local_aabb;
	i = 1;
	while (i < b->sub_count)
	{
		acc = aabb_union(acc, b->sub_shapes[i].local_aabb);
		i++;
	}
	b->global_aabb = acc;
}

void	init_compound(t_physics_body *b, t_sub_shape *bricks, size_t n)
{
	size_t	i;

	if (!b || !bricks)
		return ;
	if (n > MAX_SUB_SHAPES)
		n = MAX_SUB_SHAPES;
	i = 0;
	while (i < n)
	{
		b->sub_shapes[i] = bricks[i];
		i++;
	}
	b->sub_count = n;
	b->is_compound = true;
	compute_com(b);
	compute_inertia(b);
	update_compound(b);
}
