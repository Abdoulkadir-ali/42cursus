/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#    +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "bvh.h"
#include "libft.h"
#include <stdlib.h>

/**
 * Initializes a mesh structure, allocating memory for vertices, indices, etc.
 * @param mesh Pointer to mesh structure.
 * @param v_count Number of vertices.
 * @param i_count Number of indices.
 * @param has_uvs Whether to allocate UVs.
 * @param has_normals Whether to allocate normals.
 * @return true on success, false on allocation failure.
 */
bool	mesh_init(t_mesh *mesh, int v_count, int i_count, bool has_uvs, bool has_normals)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->vertex_count = v_count;
	mesh->tri_count = i_count / 3;
	
	if (v_count > 0)
	{
		mesh->vertices = malloc(sizeof(t_vec3) * v_count);
		if (!mesh->vertices) return (mesh_free(mesh), false);
		if (has_normals)
		{
			mesh->normals = malloc(sizeof(t_vec3) * v_count);
			if (!mesh->normals) return (mesh_free(mesh), false);
		}
		if (has_uvs)
		{
			mesh->uvs = malloc(sizeof(t_vec2) * v_count);
			if (!mesh->uvs) return (mesh_free(mesh), false);
		}
	}
	if (i_count > 0)
	{
		mesh->indices = malloc(sizeof(int) * i_count);
		if (!mesh->indices) return (mesh_free(mesh), false);
	}
	return (true);
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
	if (mesh->internal_bvh)
		bvh_destroy(mesh->internal_bvh);
	ft_memset(mesh, 0, sizeof(t_mesh));
}
