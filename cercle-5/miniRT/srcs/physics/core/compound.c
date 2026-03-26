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

/**
 * @brief Initializes a compound body from an array of Lego bricks.
 * Computes CoM and global_aabb. Caps sub_count at MAX_SUB_SHAPES.
 */
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
	update_compound(b);
}
