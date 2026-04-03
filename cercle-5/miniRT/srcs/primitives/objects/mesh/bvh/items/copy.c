/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:14:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:46:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/**
 * Copies reordered triangle indices into the mesh structure after 
 * BVH partitioning is complete. This prepares the mesh for efficient 
 * ray-tracing lookups.
 */
void	bvh_copy_indices(t_mesh *mesh, t_mbvh *bvh)
{
	size_t	tri;
	size_t	i;

	i = 0;
	while (i < mesh->tri_count)
	{
		tri = bvh->items[i].index;
		mesh->bvh_indices[i * 3 + 0] = mesh->indices[tri * 3 + 0];
		mesh->bvh_indices[i * 3 + 1] = mesh->indices[tri * 3 + 1];
		mesh->bvh_indices[i * 3 + 2] = mesh->indices[tri * 3 + 2];
		i++;
	}
}
