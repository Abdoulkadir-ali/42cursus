/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static void	mesh_free_edit(t_mesh *mesh)
{
	if (mesh->edit_snap_verts)
		free(mesh->edit_snap_verts);
	if (mesh->edit_snap_norms)
		free(mesh->edit_snap_norms);
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
	mesh_free_edit(mesh);
	ft_memset(mesh, 0, sizeof(t_mesh));
}
