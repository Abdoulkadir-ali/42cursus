/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:14:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/**
 * Calculates essential geometry information for a single triangle, 
 * including its AABB and centroid, used for BVH construction.
 */
void	bvh_get_triangle_info(t_mesh *mesh, int tri_idx, t_mesh_build_item *out)
{
	int		*idx;
	t_vec3	v0;
	t_vec3	v1;
	t_vec3	v2;

	idx = &mesh->indices[tri_idx * 3];
	v0 = mesh->vertices[idx[0]];
	v1 = mesh->vertices[idx[1]];
	v2 = mesh->vertices[idx[2]];
	out->index = tri_idx;
	out->bbox.min = vec3_min(v0, vec3_min(v1, v2));
	out->bbox.max = vec3_max(v0, vec3_max(v1, v2));
	out->bbox.min = vec3_sub(out->bbox.min, vec3(1e-4, 1e-4, 1e-4));
	out->bbox.max = vec3_add(out->bbox.max, vec3(1e-4, 1e-4, 1e-4));
	out->centroid = vec3_scale(vec3_add(v0, vec3_add(v1, v2)), 1.0 / 3.0);
}
