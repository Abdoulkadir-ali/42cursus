/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 13:38:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include <math.h>

/**
 * Converts skinned GLB-space positions (in geometry.vertices) to engine space
 * and writes them into vertices[i].pos / normals[i], which the BVH build and
 * raytracer read. Matches the axis swap used by the old animation system:
 *   engine.y = -glb.z,  engine.z = glb.y  (glTF Y-up → engine Z-up)
 * Optionally applies the .rt scene-level transform on top.
 */
void	glb_reapply_scene_transform(t_mesh *mesh)
{
	size_t	i;
	t_vec3	v;
	double	tmp;
	float	len;

	i = 0;
	while (i < mesh->vertex_count)
	{
		v = mesh->geometry.vertices[i];
		tmp = v.y;
		v.y = -v.z;
		v.z = tmp;
		mesh->vertices[i].pos = v;
		if (mesh->normals)
		{
			v = mesh->normals[i];
			tmp = v.y;
			v.y = -v.z;
			v.z = tmp;
			len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
			if (len > 0.0001f)
			{
				v.x /= len;
				v.y /= len;
				v.z /= len;
			}
			mesh->normals[i] = v;
			mesh->vertices[i].normal = v;
		}
		i++;
	}
	if (mesh->has_scene_transform)
	{
		i = 0;
		while (i < mesh->vertex_count)
		{
			mesh->vertices[i].pos = mat4_mul_pos(mesh->scene_mat,
					mesh->vertices[i].pos);
			i++;
		}
	}
}


