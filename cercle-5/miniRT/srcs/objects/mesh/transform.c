/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "raytracing.h"

void	mesh_apply_transform(t_mesh *mesh, t_transform transform)
{
	t_mat4	m;
	t_mat4	rot;
	int		i;

	if (!mesh)
		return ;
	debug_print_mesh_bake(mesh, true);
	m = mat4_transform(transform);
	rot = mat4_rotation(transform.rotation);
	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->vertices[i] = mat4_mul_pos(m, mesh->vertices[i]);
		if (i < 5)
		{
			ft_print_debug("DEBUG: Transformed v[%d]: (%.4f, %.4f, %.4f)\n", 
				i, mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z);
		}
		if (mesh->normals)
		{
			mesh->normals[i] = mat4_mul_vec3(rot, mesh->normals[i]);
			mesh->normals[i] = vec3_norm(mesh->normals[i]);
			if (i == 0) ft_print_debug("DEBUG: Transformed normal[0]: %.2f, %.2f, %.2f\n", mesh->normals[0].x, mesh->normals[0].y, mesh->normals[0].z);
		}
		i++;
	}
	mesh->bbox = aabb_create_empty();
	i = 0;
	while (i < mesh->vertex_count)
	{
		aabb_expand_point(&mesh->bbox, mesh->vertices[i]);
		i++;
	}
	/* Reset transform since we baked it */
	mesh->transform = (t_transform){0};
    mesh->transform.scale = vec3(1, 1, 1);
	debug_print_mesh_bake(mesh, false);
}
