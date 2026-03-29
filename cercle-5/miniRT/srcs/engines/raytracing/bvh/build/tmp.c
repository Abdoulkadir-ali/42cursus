/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 12:34:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "debug.h"

/**
 * @brief Builds the initial pointer-based temporary BVH tree.
 * @param scene Pointer to the scene.
 * @param total Total number of objects in the scene.
 * @param k Pointer to store the final count of collected objects.
 * @return Returns the root of the temporary tree.
 */
t_bvh_tmp_node	*build_tmp_tree(t_scene *scene, size_t total, size_t *k,
		t_build_item **final_items)
{
	t_build_item	*items;
	t_bvh_tmp_node	*root;
	size_t			count;

	DBG_TRACE_MSG(DBG_CH_BVH, "build_tmp_tree: total=%zu\n", total);
	items = malloc(sizeof(t_build_item) * total);
	if (!items)
		return (NULL);
	count = collect_objects(scene, items);
	DBG_TRACE_MSG(DBG_CH_BVH, "build_tmp_tree: collected=%zu\n", count);
	if (count == 0)
	{
		free(items);
		if (k) *k = 0;
		return (NULL);
	}
	DBG_TRACE_MSG(DBG_CH_BVH, "build_tmp_tree: calling build_recursive\n");
	root = build_recursive(items, count, items);
	DBG_TRACE_MSG(DBG_CH_BVH, "build_tmp_tree: root=%p\n", (void*)root);
	if (k)
		*k = count;
	*final_items = items;
	return (root);
}
