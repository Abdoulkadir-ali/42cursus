/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:39:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Reapplies the global scene transformation to a skinned mesh, ensuring
 * it remains correctly placed in world space even after local bone skinning.
 */
void	glb_reapply_scene_transform(t_mesh *mesh)
{
	size_t	i;
	t_vec3	v;

	i = 0;
	while (i < mesh->geometry.vertex_count)
	{
		v = mat4_mul_dir(mesh->scene_transform, mesh->geometry.vertices[i]);
		mesh->geometry.vertices[i] = v;
		if (mesh->normals)
		{
			v = mat4_mul_dir(mesh->scene_transform, mesh->normals[i]);
			mesh->normals[i] = v;
		}
		i++;
	}
}
