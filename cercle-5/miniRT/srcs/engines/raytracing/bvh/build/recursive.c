/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:09:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:04:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

#define MAX_LEAF_OBJECTS 4

static t_aabb	compute_bbox(t_build_item *items, size_t count)
{
	t_aabb	bbox;
	size_t	i;

	bbox = aabb_create_empty();
	i = 0;
	while (i < count)
		bbox = aabb_union(&bbox, &items[i++].bbox);
	aabb_expand_eps(&bbox, 1e-5);
	return (bbox);
}

static t_bvh_tmp_node	*init_leaf_node(t_build_item *items, size_t count, t_build_item *base)
{
	t_bvh_tmp_node	*node;
	size_t			i;

	node = ft_calloc(1, sizeof(t_bvh_tmp_node));
	if (!node)
		return (NULL);
	node->bbox = aabb_create_empty();
	i = 0;
	while (i < count)
		node->bbox = aabb_union(&node->bbox, &items[i++].bbox);
	aabb_expand_eps(&node->bbox, 1e-5);
	node->first_ref = (int)(items - base);
	node->num_refs = count;
	return (node);
}

static int	build_children(t_bvh_tmp_node *node, t_build_item *items,
		t_split_info info, size_t count, t_build_item *base)
{
	node->left = build_recursive(items, info.split_idx, base);
	if (!node->left)
		return (0);
	node->right = build_recursive(items + info.split_idx, count - info.split_idx,
			base);
	if (!node->right)
	{
		node_destroy(node->left);
		return (0);
	}
	return (1);
}

static t_bvh_tmp_node	*build_internal_node(t_build_item *items, size_t count,
		t_aabb bbox, t_build_item *base)
{
	t_bvh_tmp_node		*node;
	t_split_info		info;
	double				p_area;

	node = ft_calloc(1, sizeof(t_bvh_tmp_node));
	if (!node)
		return (NULL);
	node->bbox = bbox;
	p_area = aabb_surface_area(&bbox);
	info = find_best_split(items, count, p_area);
	if (info.axis == -1)
	{
		free(node);
		return (init_leaf_node(items, count, base));
	}
	if (!build_children(node, items, info, count, base))
	{
		free(node);
		return (NULL);
	}
	return (node);
}

/**
 * @brief Core recursive construction logic using the Surface Area Heuristic (SAH) 
 * to find the optimal split for each subset of objects.
 */
t_bvh_tmp_node	*build_recursive(t_build_item *items, size_t count,
		t_build_item *base)
{
	t_aabb	bbox;

	bbox = compute_bbox(items, count);
	if (count <= MAX_LEAF_OBJECTS)
		return (init_leaf_node(items, count, base));
	return (build_internal_node(items, count, bbox, base));
}
