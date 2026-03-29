/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 12:34:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "debug.h"

static size_t	total_objects(t_scene *sc)
{
	return (sc->primitives.count + sc->tri_soa.count);
}

static void	cache_assets(t_scene *scene)
{
	/* Modern DOD sync handles geometry baking (e.g. Pyramid verts)
	 * during the raytrace_engine_sync phase. Emissive cache is built 
	 * once from the material pool. */
	build_emissive_cache(scene);
}

static bool	flatten_and_alloc(t_bvh *bvh, t_bvh_tmp_node *root, size_t k,
		t_build_item *items)
{
	int	nc;
	int	rc;
	size_t i;

	DBG_TRACE_MSG(DBG_CH_BVH, "flatten_and_alloc: k=%zu\n", k);
	if (!alloc_flat(bvh, k))
	{
		node_destroy(root);
		free(items);
		return (false);
	}
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten_and_alloc: alloc_flat OK\n");
	bvh->refs = malloc(sizeof(t_bvh_ref) * k);
	if (!bvh->refs)
	{
		node_destroy(root);
		free(items);
		return (false);
	}
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten_and_alloc: refs OK, copying\n");
	i = 0;
	while (i < k)
	{
		bvh->refs[i] = items[i].ref;
		i++;
	}
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten_and_alloc: copy done, freeing items\n");
	free(items);
	nc = 0;
	rc = 0;
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten_and_alloc: calling flatten_tmp\n");
	flatten_tmp(root, bvh, &nc, &rc);
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten_and_alloc: flatten_tmp OK nc=%d\n", nc);
	bvh->num_nodes = nc;
	bvh->num_refs = k;
	node_destroy(root);
	return (true);
}

/**
 * @brief Top-level API to build the entire global BVH tree for the scene.
 * @param scene Pointer to the scene content.
 * @return Returns the primary BVH pointer or NULL on error.
 */
t_bvh	*bvh_build_global(t_scene *scene)
{
	t_bvh			*bvh;
	t_bvh_tmp_node	*root;
	size_t			k;
	t_build_item	*items;

	if (!scene)
		return (NULL);
	bvh = ft_calloc(1, sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->scene = scene;
	if (total_objects(scene) == 0)
	{
		DBG_WARN_MSG(DBG_CH_BVH, "BVH build: scene has 0 objects!\n");
		return (bvh);
	}
	DBG_INFO_MSG(DBG_CH_BVH, "BVH build: %zu objects\n", total_objects(scene));
	root = build_tmp_tree(scene, total_objects(scene), &k, &items);
	if (!root)
		return (free(bvh), NULL);
	if (!flatten_and_alloc(bvh, root, k, items))
		return (free(bvh), NULL);
	cache_assets(scene);
	DBG_INFO_MSG(DBG_CH_BVH, "BVH build done: %d nodes, %zu refs\n",
		bvh->num_nodes, k);
	return (bvh);
}
