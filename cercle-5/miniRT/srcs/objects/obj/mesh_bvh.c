/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	get_triangle_info(t_mesh *mesh, int tri_idx, t_mesh_build_item *out)
{
	int		*idx = &mesh->indices[tri_idx * 3];
	t_vec3	v0 = mesh->vertices[idx[0]];
	t_vec3	v1 = mesh->vertices[idx[1]];
	t_vec3	v2 = mesh->vertices[idx[2]];

	out->index = tri_idx;
	out->bbox.min = vec3_min(v0, vec3_min(v1, v2));
	out->bbox.max = vec3_max(v0, vec3_max(v1, v2));
	out->centroid = vec3_scale(vec3_add(v0, vec3_add(v1, v2)), 1.0 / 3.0);
}

static void	update_node_bounds(t_mbvh_node *node, t_mbvh_ctx *ctx, int first, int count)
{
	t_aabb	bbox = aabb_create_empty();
	for (int i = 0; i < count; i++)
		bbox = aabb_union(&bbox, &ctx->items[first + i].bbox);
	node->bbox = bbox;
}

/* 
** Partition items based on the split centroid value. 
** Returns the index of the first item in the second partition.
*/
static int	partition_items(t_mesh_build_item *items, int count, int axis, double split_val)
{
	int	left = 0;
	int	right = count - 1;

	while (left <= right)
	{
		double c_val;
		if (axis == 0) c_val = items[left].centroid.x;
		else if (axis == 1) c_val = items[left].centroid.y;
		else c_val = items[left].centroid.z;

		if (c_val < split_val)
		{
			left++;
		}
		else
		{
			/* Swap with right */
			t_mesh_build_item tmp = items[left];
			items[left] = items[right];
			items[right] = tmp;
			right--;
		}
	}
	return (left);
}

static int	build_recursive(t_mbvh_ctx *ctx, int first, int count)
{
	int		node_idx = ctx->node_count++;
	t_mbvh_node *node = &ctx->nodes[node_idx];

	/* 1. Compute bounds for this node */
	update_node_bounds(node, ctx, first, count);

	/* 2. Leaf condition */
	if (count <= 4)
	{
		node->left_or_first = first;
		node->count = count;
		return (node_idx);
	}

	/* 3. Determine split plane using Binned SAH */
	t_aabb	centroid_bounds = aabb_create_empty();
	for (int i = 0; i < count; i++)
		aabb_expand_point(&centroid_bounds, ctx->items[first + i].centroid);

	int		best_axis = -1;
	double	best_cost = (double)count; /* Cost of remaining as leaf (intersection cost = 1) */
	double	split_pos = 0;

	for (int axis = 0; axis < 3; axis++)
	{
		double min_val, max_val;
		if (axis == 0) { min_val = centroid_bounds.min.x; max_val = centroid_bounds.max.x; }
		else if (axis == 1) { min_val = centroid_bounds.min.y; max_val = centroid_bounds.max.y; }
		else { min_val = centroid_bounds.min.z; max_val = centroid_bounds.max.z; }

		if (max_val - min_val < 1e-5) continue;

		t_bin	bins[BVH_BINS];
		for (int b = 0; b < BVH_BINS; b++) { bins[b].count = 0; bins[b].bounds = aabb_create_empty(); }

		double	scale = BVH_BINS / (max_val - min_val);
		for (int i = 0; i < count; i++)
		{
			double val;
			if (axis == 0) val = ctx->items[first + i].centroid.x;
			else if (axis == 1) val = ctx->items[first + i].centroid.y;
			else val = ctx->items[first + i].centroid.z;
			
			int bin_idx = (int)((val - min_val) * scale);
			if (bin_idx >= BVH_BINS) bin_idx = BVH_BINS - 1;
			if (bin_idx < 0) bin_idx = 0;
			
			bins[bin_idx].count++;
			bins[bin_idx].bounds = aabb_union(&bins[bin_idx].bounds, &ctx->items[first + i].bbox);
		}

		/* Evaluate potential splits (between bins) */
		double	parent_sa = aabb_surface_area(node->bbox);
		t_aabb	left_box = aabb_create_empty();
		int		left_count = 0;
		double	left_area[BVH_BINS - 1];
		int		left_counts[BVH_BINS - 1];

		/* Sweep Left -> Right */
		for (int i = 0; i < BVH_BINS - 1; i++)
		{
			left_count += bins[i].count;
			left_box = aabb_union(&left_box, &bins[i].bounds);
			left_counts[i] = left_count;
			left_area[i] = aabb_surface_area(left_box);
		}

		/* Sweep Right -> Left and evaluate cost */
		t_aabb	right_box = aabb_create_empty();
		int		right_count = 0;
		for (int i = BVH_BINS - 1; i > 0; i--)
		{
			right_count += bins[i].count;
			right_box = aabb_union(&right_box, &bins[i].bounds);
			
			int l_c = left_counts[i - 1];
			if (l_c == 0 || right_count == 0) continue;

			double cost = 1.0 + (left_area[i - 1] / parent_sa) * l_c + (aabb_surface_area(right_box) / parent_sa) * right_count;
			if (cost < best_cost)
			{
				best_cost = cost;
				best_axis = axis;
				split_pos = min_val + (i * (max_val - min_val)) / BVH_BINS;
			}
		}
	}

	if (best_axis == -1)
	{
		node->left_or_first = first;
		node->count = count;
		return (node_idx);
	}

	/* 4. Partition and Recurse */
	int mid = partition_items(ctx->items + first, count, best_axis, split_pos);
	
	/* Fallback if partition failed to split items (e.g. all same centroid) */
	if (mid <= 0 || mid >= count)
	{
		node->left_or_first = first;
		node->count = count;
		return (node_idx);
	}

	node->count = 0; /* Interior node */
	node->axis = best_axis;
	
	build_recursive(ctx, first, mid);
	node->left_or_first = build_recursive(ctx, first + mid, count - mid);
	
	return (node_idx);
}

void	mesh_build_bvh(t_mesh *mesh)
{
	t_mbvh_ctx	ctx;

	if (!mesh || mesh->tri_count == 0) return ;
	
	ctx.items = malloc(sizeof(t_mesh_build_item) * mesh->tri_count);
	if (!ctx.items) return ;

	for (int i = 0; i < mesh->tri_count; i++) 
		get_triangle_info(mesh, i, &ctx.items[i]);
	
	mesh->bvh_nodes = ft_calloc(mesh->tri_count * 2, sizeof(t_mbvh_node));
	mesh->bvh_indices = malloc(sizeof(int) * mesh->tri_count * 3);
	if (!mesh->bvh_nodes || !mesh->bvh_indices)
	{
		free(ctx.items);
		return ;
	}

	ctx.nodes = mesh->bvh_nodes;
	ctx.node_count = 0;
	
	build_recursive(&ctx, 0, mesh->tri_count);
	
	/* Copy final optimized indices */
	for (int i = 0; i < mesh->tri_count; i++)
	{
		int tri = ctx.items[i].index;
		mesh->bvh_indices[i * 3 + 0] = mesh->indices[tri * 3 + 0];
		mesh->bvh_indices[i * 3 + 1] = mesh->indices[tri * 3 + 1];
		mesh->bvh_indices[i * 3 + 2] = mesh->indices[tri * 3 + 2];
	}
	
	free(ctx.items);
	// printf("Mesh BVH built: %d nodes for %d tris\n", ctx.node_count, mesh->tri_count);
}
