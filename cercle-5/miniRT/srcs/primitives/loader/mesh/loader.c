/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:22:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/* Scene-aware injection wrappers. Prefer format-specific scene loaders when
 * available (OBJ already implements direct-to-scene). Otherwise fall back to
 * raw-model path and convert into the scene via scene_add_raw_model.
 */
bool	load_mesh_file(t_scene *scene, const char *path)
{
	const char *ext;

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
	return (false);
}

bool	load_injected_mesh(t_scene *scene, const char *path,
			t_transform transform, t_vec3 color, t_vec3 emission)
{
	(void)transform; (void)color; (void)emission;
	return (load_mesh_file(scene, path));
}
bool	mesh_load_from_file(t_mesh *mesh, const char *path)
{
	const char *ext;
	t_obj obj;

	if (!validate_file(path))
		return (false);
	ext = get_file_extension(path);
	if (ft_strcmp(ext, "obj") == 0)
	{
		if (!obj_parse_to_asset(&obj, path))
			return (false);
		obj_init_mesh(mesh, &obj, path);
		obj_free_obj(&obj);
		return (true);
	}
	return (false);
}
