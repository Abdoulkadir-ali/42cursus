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

#include "loader.h"

static bool	alloc_vertex_data(t_mesh *mesh, t_mesh_init init)
{
	if (init.v_count <= 0)
		return (true);
	mesh->vertices = malloc(sizeof(t_vec3) * init.v_count);
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
	mesh->indices = malloc(sizeof(int) * init.i_count);
	if (!mesh->indices)
		return (false);
	return (true);
}

static void	mesh_base_init(t_mesh *mesh)
{
 	ft_memset(mesh, 0, sizeof(t_mesh));
 	mesh->transform.scale = vec3(1, 1, 1);
 	mesh->group_id = -1;
}

bool	mesh_init(t_mesh *mesh, t_mesh_init init)
{
	mesh_base_init(mesh);
	mesh->vertex_count = init.v_count;
	mesh->tri_count = init.i_count / 3;
	if (!alloc_vertex_data(mesh, init))
		return (mesh_free(mesh), false);
	if (!alloc_index_data(mesh, init))
		return (mesh_free(mesh), false);
	return (true);
}

void	init_mesh(t_mesh *mesh, const char *path)
{
	mesh_base_init(mesh);
	if (path)
		mesh->name = ft_strdup(path);
	mesh->bbox = aabb_create_empty();
}

/**
 * Frees all dynamic memory associated with a mesh.
 */
void	mesh_free(t_mesh *mesh)
{
	if (!mesh)
		return ;
	if (mesh->vertices)
		free(mesh->vertices);
	if (mesh->normals)
		free(mesh->normals);
	if (mesh->uvs)
		free(mesh->uvs);
	if (mesh->indices)
		free(mesh->indices);
	if (mesh->name)
		free(mesh->name);
	if (mesh->bvh_nodes)
		free(mesh->bvh_nodes);
	if (mesh->bvh_indices)
		free(mesh->bvh_indices);
	if (mesh->tri_cache)
		free(mesh->tri_cache);
	if (mesh->edit_snap_verts)
		free(mesh->edit_snap_verts);
	if (mesh->edit_snap_norms)
		free(mesh->edit_snap_norms);
	ft_memset(mesh, 0, sizeof(t_mesh));
}
