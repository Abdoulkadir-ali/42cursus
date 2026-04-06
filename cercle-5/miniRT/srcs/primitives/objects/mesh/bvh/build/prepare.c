/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:55:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static bool	bvh_alloc_nodes(t_mbvh *bvh, t_mesh *mesh)
{
	if (mesh->bvh_nodes)
		free(mesh->bvh_nodes);
	if (mesh->bvh_indices)
		free(mesh->bvh_indices);
	mesh->bvh_nodes = ft_calloc(mesh->tri_count * 2, sizeof(t_mbvh_node));
	mesh->bvh_indices = malloc(sizeof(*mesh->bvh_indices) * mesh->tri_count * 3);
	if (!mesh->bvh_nodes || !mesh->bvh_indices)
	{
		free(bvh->items);
		return (false);
	}
	bvh->nodes = mesh->bvh_nodes;
	bvh->node_count = 0;
	return (true);
}

/**
 * Prepares the BVH build context, including temporary storage for 
 * triangle centroids and final spatial node allocation.
 */
bool	bvh_prepare(t_mbvh *bvh, t_mesh *mesh)
{
	size_t	i;

	bvh->items = malloc(sizeof(t_mesh_build_item) * mesh->tri_count);
	if (!bvh->items)
		return (false);
	i = 0;
	while (i < mesh->tri_count)
	{
		bvh_get_triangle_info(mesh, i, &bvh->items[i]);
		i++;
	}
	return (bvh_alloc_nodes(bvh, mesh));
}
