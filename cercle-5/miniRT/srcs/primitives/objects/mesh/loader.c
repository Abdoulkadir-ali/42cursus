/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	load_mesh_file(const char *path, t_raw_model *out)
{
	const char	*ext;

	if (!validate_file(path))
		return (false);
	ext = get_file_extension(path);
	ft_memset(out, 0, sizeof(t_raw_model));
	if (ft_strcmp(ext, "fbx") == 0)
		return (fbx_load(path, out));
	if (ft_strcmp(ext, "obj") == 0)
		return (obj_load(path, out));
	if (ft_strcmp(ext, "fdf") == 0)
		return (fdf_load(path, out));
	if (ft_strcmp(ext, "glb") == 0)
		return (glb_load(path, out));
	return (false);
}

bool	load_injected_mesh(const char *path, t_raw_model *out, t_transform transform, t_vec3 color, t_vec3 emission)
{
	if (!load_mesh_file(path, out))
		return (false);
	model_apply_transform(out, transform);
	model_apply_material_override(out, color, emission);
	return (true);
}
