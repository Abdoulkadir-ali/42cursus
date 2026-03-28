/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

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

static bool	flatten_and_alloc(t_bvh *bvh, t_bvh_tmp_node *root, size_t k)
{
	int	nc;
	int	rc;

	if (!alloc_flat(bvh, k))
	{
		node_destroy(root);
		return (false);
	}
	nc = 0;
	rc = 0;
	flatten_tmp(root, bvh, &nc, &rc);
	bvh->num_nodes = nc;
	bvh->num_refs = rc;
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

	if (!scene)
		return (NULL);
	bvh = ft_calloc(1, sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->scene = scene;
	if (total_objects(scene) == 0)
		return (bvh);
	root = build_tmp_tree(scene, total_objects(scene), &k);
	if (!root)
		return (free(bvh), NULL);
	if (k == 0)
		return (node_destroy(root), bvh);
	if (!flatten_and_alloc(bvh, root, k))
		return (free(bvh), NULL);
	cache_assets(scene);
	return (bvh);
}
