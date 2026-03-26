/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:05:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Initializes a leaf node in the BVH tree, containing actual object 
 * references rather than children.
 */
t_bvh_tmp_node	*init_leaf_node(t_build_item *items, size_t count)
{
	t_bvh_tmp_node	*node;
	size_t			i;

	node = ft_calloc(1, sizeof(t_bvh_tmp_node));
	if (!node)
		return (NULL);
	node->bbox = aabb_create_empty();
	i = 0;
	while (i < count)
		aabb_expand_point(&node->bbox, items[i++].bbox.min);
	i = 0;
	while (i < count)
		aabb_expand_point(&node->bbox, items[i++].bbox.max);
	aabb_expand_eps(&node->bbox, 1e-5);
	node->refs = malloc(sizeof(t_bvh_ref) * count);
	if (!node->refs)
		return (free(node), NULL);
	i = 0;
	while (i < count)
	{
		node->refs[i] = items[i].ref;
		i++;
	}
	node->num_refs = count;
	return (node);
}
