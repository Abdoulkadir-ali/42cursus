/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 05:05:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static int	compare_x(const void *a, const void *b)
{
	const t_mesh_build_item *ia = a;
	const t_mesh_build_item *ib = b;
	if (ia->centroid.x < ib->centroid.x) return (-1);
	return (1);
}

static int	compare_y(const void *a, const void *b)
{
	const t_mesh_build_item *ia = a;
	const t_mesh_build_item *ib = b;
	if (ia->centroid.y < ib->centroid.y) return (-1);
	return (1);
}

static int	compare_z(const void *a, const void *b)
{
	const t_mesh_build_item *ia = a;
	const t_mesh_build_item *ib = b;
	if (ia->centroid.z < ib->centroid.z) return (-1);
	return (1);
}

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

typedef struct s_mbvh_ctx
{
	t_mesh_build_item	*items;
	t_mbvh_node			*nodes;
	int					*tri_indices;
	int					node_count;
}	t_mbvh_ctx;

static int	build_flat(t_mbvh_ctx *ctx, int first, int count)
{
	int		node_idx = ctx->node_count++;
	t_aabb	bbox = aabb_create_empty();
	for (int i = 0; i < count; i++)
		bbox = aabb_union(&bbox, &ctx->items[first + i].bbox);
	ctx->nodes[node_idx].bbox = bbox;

	/* SAH Split evaluation */
	if (count <= 4)
	{
		ctx->nodes[node_idx].left_or_first = first;
		ctx->nodes[node_idx].count = count;
		return (node_idx);
	}

	double	best_cost = (double)count;
	int		best_axis = -1;
	int		best_split = -1;
	double	parent_area = aabb_surface_area(bbox);

	for (int axis = 0; axis < 3; axis++)
	{
		if (axis == 0) qsort(ctx->items + first, count, sizeof(t_mesh_build_item), compare_x);
		else if (axis == 1) qsort(ctx->items + first, count, sizeof(t_mesh_build_item), compare_y);
		else qsort(ctx->items + first, count, sizeof(t_mesh_build_item), compare_z);

		for (int s = 1; s < 16; s++)
		{
			int split = (count * s) / 16;
			if (split < 1 || split >= count) continue;
			t_aabb left_box = aabb_create_empty();
			t_aabb right_box = aabb_create_empty();
			for (int k = 0; k < split; k++) left_box = aabb_union(&left_box, &ctx->items[first + k].bbox);
			for (int k = split; k < count; k++) right_box = aabb_union(&right_box, &ctx->items[first + k].bbox);
			double cost = 1.0 + (aabb_surface_area(left_box) / parent_area) * split + (aabb_surface_area(right_box) / parent_area) * (count - split);
			if (cost < best_cost) { best_cost = cost; best_axis = axis; best_split = split; }
		}
	}

	if (best_axis == -1) /* Leaf check */
	{
		ctx->nodes[node_idx].left_or_first = first;
		ctx->nodes[node_idx].count = count;
		return (node_idx);
	}

	if (best_axis == 0) qsort(ctx->items + first, count, sizeof(t_mesh_build_item), compare_x);
	else if (best_axis == 1) qsort(ctx->items + first, count, sizeof(t_mesh_build_item), compare_y);
	
	ctx->nodes[node_idx].count = 0;
	ctx->nodes[node_idx].axis = best_axis;
	build_flat(ctx, first, best_split);
	ctx->nodes[node_idx].left_or_first = build_flat(ctx, first + best_split, count - best_split);
	return (node_idx);
}

void	mesh_build_bvh(t_mesh *mesh)
{
	t_mbvh_ctx	ctx;

	if (!mesh || mesh->tri_count == 0) return ;
	ctx.items = malloc(sizeof(t_mesh_build_item) * mesh->tri_count);
	for (int i = 0; i < mesh->tri_count; i++) get_triangle_info(mesh, i, &ctx.items[i]);
	
	mesh->bvh_nodes = ft_calloc(mesh->tri_count * 2, sizeof(t_mbvh_node));
	mesh->bvh_indices = malloc(sizeof(int) * mesh->tri_count * 3);
	ctx.nodes = mesh->bvh_nodes;
	ctx.node_count = 0;
	
	build_flat(&ctx, 0, mesh->tri_count);
	
	/* Copy final optimized indices */
	for (int i = 0; i < mesh->tri_count; i++)
	{
		int tri = ctx.items[i].index;
		mesh->bvh_indices[i * 3 + 0] = mesh->indices[tri * 3 + 0];
		mesh->bvh_indices[i * 3 + 1] = mesh->indices[tri * 3 + 1];
		mesh->bvh_indices[i * 3 + 2] = mesh->indices[tri * 3 + 2];
	}
	free(ctx.items);
}
