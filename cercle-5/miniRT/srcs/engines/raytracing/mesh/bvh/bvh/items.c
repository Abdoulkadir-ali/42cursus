/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static double	bvh_item_centroid(t_mesh_build_item *items, int idx, int axis)
{
	if (axis == 0)
		return (items[idx].centroid.x);
	if (axis == 1)
		return (items[idx].centroid.y);
	return (items[idx].centroid.z);
}

static void	bvh_swap_item(t_mesh_build_item *items, int left, int right)
{
	t_mesh_build_item	tmp;

	tmp = items[left];
	items[left] = items[right];
	items[right] = tmp;
}

void	bvh_get_triangle_info(t_mesh *mesh, int tri_idx, t_mesh_build_item *out)
{
	int		*idx;
	t_vec3	v0;
	t_vec3	v1;
	t_vec3	v2;

	idx = &mesh->indices[tri_idx * 3];
	v0 = mesh->vertices[idx[0]];
	v1 = mesh->vertices[idx[1]];
	v2 = mesh->vertices[idx[2]];
	out->index = tri_idx;
	out->bbox.min = vec3_min(v0, vec3_min(v1, v2));
	out->bbox.max = vec3_max(v0, vec3_max(v1, v2));
	out->bbox.min = vec3_sub(out->bbox.min, vec3(1e-4, 1e-4, 1e-4));
	out->bbox.max = vec3_add(out->bbox.max, vec3(1e-4, 1e-4, 1e-4));
	out->centroid = vec3_scale(vec3_add(v0, vec3_add(v1, v2)), 1.0 / 3.0);
}

int	bvh_partition_items(t_mesh_build_item *items, int count, int axis,
		double split_val)
{
	int		left;
	int		right;
	double	c_val;

	left = 0;
	right = count - 1;
	while (left <= right)
	{
		c_val = bvh_item_centroid(items, left, axis);
		if (c_val < split_val)
			left++;
		else
		{
			bvh_swap_item(items, left, right);
			right--;
		}
	}
	return (left);
}

void	bvh_copy_indices(t_mesh *mesh, t_mbvh_ctx *ctx)
{
	int		tri;
	int		i;

	i = 0;
	while (i < mesh->tri_count)
	{
		tri = ctx->items[i].index;
		mesh->bvh_indices[i * 3 + 0] = mesh->indices[tri * 3 + 0];
		mesh->bvh_indices[i * 3 + 1] = mesh->indices[tri * 3 + 1];
		mesh->bvh_indices[i * 3 + 2] = mesh->indices[tri * 3 + 2];
		i++;
	}
}
