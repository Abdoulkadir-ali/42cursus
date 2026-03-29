/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:26:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "debug.h"

/* Scene-aware injection wrappers. Prefer format-specific scene loaders when
 * available (OBJ already implements direct-to-scene). Otherwise fall back to
 * raw-model path and convert into the scene via scene_add_raw_model.
 */
bool	load_mesh_file(t_scene *scene, const char *path)
{
	const char *ext;

	DBG_INFO_MSG(DBG_CH_PARSER, "load_mesh_file: '%s'\n", path);
	if (!validate_file(path))
		return (false);
	ext = get_file_extension(path);
	DBG_TRACE_MSG(DBG_CH_PARSER, "load_mesh_file: ext='%s'\n", ext);
	if (ft_strcmp(ext, "obj") == 0)
		return (obj_load(scene, path));
	if (ft_strcmp(ext, "fbx") == 0)
		return (fbx_load(scene, path));
	if (ft_strcmp(ext, "glb") == 0)
		return (glb_load(scene, path));
	if (ft_strcmp(ext, "fdf") == 0)
		return (fdf_load(scene, path));
	DBG_WARN_MSG(DBG_CH_PARSER, "load_mesh_file: unsupported ext '%s'\n", ext);
	return (false);
}

bool	mesh_load_from_file(t_mesh_asset *mesh, const char *path)
{
	const char *ext;
	t_obj obj;

	DBG_INFO_MSG(DBG_CH_PARSER, "mesh_load_from_file: '%s'\n", path);
	if (!validate_file(path))
		return (false);
	ext = get_file_extension(path);
	DBG_TRACE_MSG(DBG_CH_PARSER, "mesh_load_from_file: ext='%s'\n", ext);
	if (ft_strcmp(ext, "obj") == 0)
	{
		if (!obj_parse_to_asset(&obj, path))
			return (false);
		obj_init_mesh(mesh, &obj);
		obj_free_obj(&obj);
		return (true);
	}
	DBG_WARN_MSG(DBG_CH_PARSER, "mesh_load_from_file: unsupported ext '%s'\n", ext);
	return (false);
}
