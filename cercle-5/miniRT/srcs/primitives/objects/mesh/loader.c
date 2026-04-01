/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:48:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:53:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

#include "scene.h"

/**
 * High-level orchestrator for mesh file integration.
 * Resolves the appropriate format loader based on file extension
 * and orchestrates the injection of assets into the global scene.
 */
bool	scene_add_mesh_file(t_scene *scene, const char *path)
{
	const char	*ext;

	ext = ft_strrchr(path, '.');
	if (!ext)
		return (false);
	if (ft_strcmp(ext, ".fbx") == 0)
		return (parse_fbx(path, scene));
	if (ft_strcmp(ext, ".obj") == 0)
		return (parse_obj(path, scene));
	if (ft_strcmp(ext, ".fdf") == 0)
		return (parse_fdf(path, scene));
	if (ft_strcmp(ext, ".glb") == 0)
		return (parse_glb(path, scene));
	return (false);
}

/**
 * High-level orchestration for loading a mesh file into a resource container.
 * This is used for caching and per-instance material modifications.
 * Maps the format-specific loading calls (which are scene-oriented)
 * to the t_mesh_resource target.
 */
bool	mesh_build_resource(const char *path, const char *ext,
			t_mesh_resource *res)
{
	t_scene	tmp;
	bool	ret;

	ft_memset(&tmp, 0, sizeof(tmp));
	ret = scene_add_mesh_file(&tmp, path);
	if (ret)
	{
		res->meshes = tmp.meshes;
		res->mesh_count = tmp.mesh_count;
		res->mesh_cap = tmp.mesh_cap;
		res->materials = tmp.materials;
		res->mat_count = tmp.mat_count;
		res->mat_cap = tmp.mat_cap;
		res->groups = tmp.groups;
		res->group_count = tmp.group_count;
		res->group_cap = tmp.group_cap;
	}
	(void)ext;
	return (ret);
}
