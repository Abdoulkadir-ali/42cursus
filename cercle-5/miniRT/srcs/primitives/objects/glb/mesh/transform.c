/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 02:58:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	apply_norm(t_mesh *mesh, size_t i)
{
	t_vec3	v;
	double	tmp;
	float	len;

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

static void	glb_to_engine_space(t_mesh *mesh)
{
	size_t	i;
	t_vec3	v;
	double	tmp;

	i = 0;
	while (i < mesh->vertex_count)
	{
		v = mesh->geometry.vertices[i];
		tmp = v.y;
		v.y = -v.z;
		v.z = tmp;
		mesh->vertices[i].pos = v;
		if (mesh->normals)
			apply_norm(mesh, i);
		i++;
	}
}

void	glb_reapply_scene_transform(t_mesh *mesh)
{
	size_t	i;

	if (!mesh->vertices || mesh->vertex_count == 0)
		return ;
	glb_to_engine_space(mesh);
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
