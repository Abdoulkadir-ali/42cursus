/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:55:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static bool	alloc_vertex_data(t_mesh *mesh, t_mesh_init init)
{
	if (init.v_count <= 0)
		return (true);
	mesh->vertices = ft_calloc(init.v_count, sizeof(t_vertex));
	if (!mesh->vertices)
		return (false);
	if (init.has_normals)
	{
		mesh->normals = malloc(sizeof(t_vec3) * init.v_count);
		if (!mesh->normals)
			return (false);
	}
	if (init.has_uvs)
	{
		mesh->uvs = malloc(sizeof(t_vec2) * init.v_count);
		if (!mesh->uvs)
			return (false);
	}
	return (true);
}

static bool	alloc_index_data(t_mesh *mesh, t_mesh_init init)
{
	if (init.i_count <= 0)
		return (true);
	mesh->indices = malloc(sizeof(*mesh->indices) * init.i_count);
	if (!mesh->indices)
		return (false);
	return (true);
}

/**
 * Initializes a mesh structure based on the provided init parameters.
 */
bool	mesh_init(t_mesh *mesh, t_mesh_init init)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->transform.scale = vec3(1, 1, 1);
	mesh->group_id = init_index(0, true);
	mesh->vertex_count = init.v_count;
	mesh->tri_count = init.i_count / 3;
	if (!alloc_vertex_data(mesh, init))
		return (mesh_free(mesh), false);
	if (!alloc_index_data(mesh, init))
		return (mesh_free(mesh), false);
	return (true);
}
