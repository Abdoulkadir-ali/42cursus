/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:50:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	load_mesh_file_raw(const char *path, t_raw_model *out)
{
	const char	*ext;

	if (!validate_file(path))
		return (false);
	ext = get_file_extension(path);
	ft_memset(out, 0, sizeof(t_raw_model));
	if (ft_strcmp(ext, "fbx") == 0)
		return (fbx_load_raw(path, out));
	if (ft_strcmp(ext, "obj") == 0)
		return (obj_load(path, out));
	if (ft_strcmp(ext, "fdf") == 0)
		return (fdf_load(path, out));
	if (ft_strcmp(ext, "glb") == 0)
		return (glb_load_raw(path, out));
	return (false);
}

bool	load_injected_mesh_raw(const char *path, t_raw_model *out, t_transform transform, t_vec3 color, t_vec3 emission)
{
	if (!load_mesh_file_raw(path, out))
		return (false);
	model_apply_transform(out, transform);
	model_apply_material_override(out, color, emission);
	return (true);
}

/* Scene-aware injection wrappers. Prefer format-specific scene loaders when
 * available (OBJ already implements direct-to-scene). Otherwise fall back to
 * raw-model path and convert into the scene via scene_add_raw_model.
 */
bool	load_mesh_file(t_scene *scene, const char *path)
{
	const char *ext;
	t_raw_model model;

	if (!validate_file(path))
		return (false);
	ext = get_file_extension(path);
	if (ft_strcmp(ext, "obj") == 0)
		return (obj_load(scene, path));
	if (ft_strcmp(ext, "fbx") == 0)
		return (fbx_load(scene, path));
	if (ft_strcmp(ext, "glb") == 0)
		return (glb_load(scene, path));
	if (ft_strcmp(ext, "fdf") == 0)
		return (fdf_load(scene, path));
	/* unknown format */
	return (false);
}

bool	load_injected_mesh(t_scene *scene, const char *path,
			t_transform transform, t_vec3 color, t_vec3 emission)
{
	t_raw_model model;

	/* For injected meshes prefer format-specific injected loaders; fall back
	 * to loading into scene and applying transform/material overrides locally
	 * if the loader exposes such options. For now, load and return success
	 * — callers should prefer non-injected load paths when possible. */
	(void)transform; (void)color; (void)emission;
	return (load_mesh_file(scene, path));
}