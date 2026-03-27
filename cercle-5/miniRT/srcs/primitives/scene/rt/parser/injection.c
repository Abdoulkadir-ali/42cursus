/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_injection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:02:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Logic for injecting an object file into a scene during RT parsing.
 * Now it is oblivious to the transformation/material logic.
 */
bool	handle_mesh_injection_internal(t_scene *scene, t_mesh_info *info, t_type type)
{
	int			start_tri;

	(void)type;
	start_tri = scene->tri_count;
	if (mesh_cache_has(info->path))
	{
		if (!mesh_cache_restore(info->path, scene))
			return (false);
	}
	else
	{
		if (!load_injected_mesh(scene, info->path, info->transform,
				info->color, info->emission))
			return (false);
		mesh_cache_save(info->path, scene, start_tri);
	}
	if (scene->tri_count > start_tri)
		scene_add_group_for_subs(scene, info->path, start_tri);
	free(info->path);
	return (true);
}
