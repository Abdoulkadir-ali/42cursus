/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 02:40:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "debug.h"

/**
 * High-level entry point for building a Mesh's Bounding Volume Hierarchy. 
 * It manages the build lifecycle, from context allocation and recursive 
 * construction to final index synchronization and cache generation.
 */
void	mesh_build_bvh(t_mesh *mesh)
{
	t_mbvh	bvh;

	if (!mesh || mesh->tri_count == 0)
		return ;
	if (!bvh_prepare(&bvh, mesh))
		return ;
	bvh.max_depth = 0;
	build_mesh_recursive(&bvh, 0, mesh->tri_count, 0);
	bvh_copy_indices(mesh, &bvh);
	mesh->bvh_node_count = bvh.node_count;
	if (bvh.node_count > 0)
		mesh->bbox = bvh.nodes[0].bbox;
	mesh_build_tri_cache(mesh);
	debug_print_bvh_build(mesh->tri_count, bvh.max_depth, false);
	ft_print_debug("DEBUG: Mesh BVH built: %lu nodes for %lu tris\n",
		bvh.node_count, mesh->tri_count);
	free(bvh.items);
}
