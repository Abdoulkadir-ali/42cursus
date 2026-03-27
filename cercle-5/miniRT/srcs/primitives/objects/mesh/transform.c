/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 20:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	apply_v_t(t_mesh *mesh, t_mat4 rot, t_vec3 pos, t_vec3 scale)
{
	int		i;
	t_vec3	v;

	i = 0;
	while (i < mesh->vertex_count)
	{
		v = mesh->vertices[i];
		v = vec3(v.x * scale.x, v.y * scale.y, v.z * scale.z);
		v = mat4_mul_vec3(rot, v);
		mesh->vertices[i] = vec3_add(v, pos);
		i++;
	}
}

static void	apply_n_t(t_mesh *mesh, t_mat4 rot)
{
	int	i;

	if (!mesh->normals)
		return ;
	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->normals[i] = vec3_norm(mat4_mul_vec3(rot, mesh->normals[i]));
		i++;
	}
}

void	mesh_apply_transform(t_mesh *mesh, t_transform transform)
{
	t_mat4	rot;

	rot = mat4_rotation(transform.rotation);
	apply_v_t(mesh, rot, transform.pos, transform.scale);
	apply_n_t(mesh, rot);
}
