/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/02/15 03:05:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:05:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "raytracing.h"

t_bvh_tmp_node	*init_leaf_node(t_build_item *items, size_t count)
{
	t_bvh_tmp_node	*node;
	size_t		i;

	node = ft_calloc(1, sizeof(t_bvh_tmp_node));
	if (!node)
		return (NULL);
	node->bbox = aabb_create_empty();
	i = 0;
	while (i < count)
		node->bbox = aabb_union(&node->bbox, &items[i++].bbox);
	node->bbox.min = vec3_sub(node->bbox.min, vec3(1e-5, 1e-5, 1e-5));
	node->bbox.max = vec3_add(node->bbox.max, vec3(1e-5, 1e-5, 1e-5));
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
