/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:09:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:09:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_aabb	compute_bbox(t_build_item *items, size_t count)
{
	t_aabb	bbox;
	size_t	i;

	bbox = aabb_create_empty();
	i = 0;
	while (i < count)
		bbox = aabb_union(&bbox, &items[i++].bbox);
	bbox.min = vec3_sub(bbox.min, vec3(1e-5, 1e-5, 1e-5));
	bbox.max = vec3_add(bbox.max, vec3(1e-5, 1e-5, 1e-5));
	return (bbox);
}

static void	sort_items_by_axis(t_build_item *items, size_t count, int axis)
{
	if (axis == 0)
		qsort(items, count, sizeof(t_build_item), compare_x);
	else if (axis == 1)
		qsort(items, count, sizeof(t_build_item), compare_y);
	else
		qsort(items, count, sizeof(t_build_item), compare_z);
}

static int	build_children(t_bvh_node *node, t_build_item *items,
		t_split_info info, size_t count)
{
	sort_items_by_axis(items, count, info.axis);
	node->left = build_recursive(items, info.split);
	if (!node->left)
		return (0);
	node->right = build_recursive(items + info.split, count - info.split);
	if (!node->right)
	{
		node_destroy(node->left);
		return (0);
	}
	return (1);
}

static t_bvh_node	*build_internal_node(t_build_item *items, size_t count,
		t_aabb bbox)
{
	t_bvh_node		*node;
	t_split_info	info;
	double			p_area;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->bbox = bbox;
	p_area = aabb_surface_area(bbox);
	info = find_best_split(items, count, p_area);
	if (info.axis == -1)
	{
		free(node);
		return (init_leaf_node(items, count));
	}
	if (!build_children(node, items, info, count))
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_bvh_node	*build_recursive(t_build_item *items, size_t count)
{
	t_aabb	bbox;

	bbox = compute_bbox(items, count);
	if (count <= MAX_LEAF_OBJECTS)
		return (init_leaf_node(items, count));
	return (build_internal_node(items, count, bbox));
}
