/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:20:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	restore_geo(t_mesh *mesh, const t_cache_snap *snap)
{
	mesh->vertices = malloc(sizeof(t_vec3) * snap->vertex_count);
	if (!mesh->vertices)
		return (mesh_free(mesh), false);
	ft_memcpy(mesh->vertices, snap->vertices,
		sizeof(t_vec3) * snap->vertex_count);
	mesh->indices = malloc(sizeof(size_t) * snap->tri_count * 3);
	if (!mesh->indices)
		return (mesh_free(mesh), false);
	ft_memcpy(mesh->indices, snap->indices,
		sizeof(size_t) * snap->tri_count * 3);
	if (snap->normals)
	{
		mesh->normals = malloc(sizeof(t_vec3) * snap->vertex_count);
		if (!mesh->normals)
			return (mesh_free(mesh), false);
		ft_memcpy(mesh->normals, snap->normals,
			sizeof(t_vec3) * snap->vertex_count);
	}
	return (true);
}

static bool	restore_one(const t_cache_snap *snap, t_scene *scene)
{
	t_mesh	mesh;
	int		inst_mat;

	ft_memset(&mesh, 0, sizeof(t_mesh));
	mesh.transform.scale = vec3(1, 1, 1);
	mesh.group_id = -1;
	mesh.vertex_count = snap->vertex_count;
	mesh.tri_count = snap->tri_count;
	inst_mat = scene_clone_material(scene, snap->mat_id);
	if (inst_mat >= 0)
		mesh.mat_id = inst_mat;
	else
		mesh.mat_id = snap->mat_id;
	if (snap->name)
		mesh.name = ft_strdup(snap->name);
	else
		mesh.name = ft_strdup("");
	if (!mesh.name || !restore_geo(&mesh, snap))
		return (false);
	return (scene_add_mesh(scene, mesh));
}

bool	mesh_cache_restore(t_scene *scene, const char *path)
{
	int	idx;
	int	i;

	idx = find_cache_idx(scene, path);
	if (idx < 0)
		return (false);
	i = 0;
	while ((size_t)i < get_cache_entry(scene, idx)->count)
	{
		if (!restore_one(&get_cache_entry(scene, idx)->snaps[i], scene))
			return (false);
		i++;
	}
	return (true);
}
