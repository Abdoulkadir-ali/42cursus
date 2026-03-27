/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:02:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:45:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Logic for injecting an object file into a scene during RT parsing.
 * Now it is oblivious to the transformation/material logic.
 */
bool	handle_mesh_injection_internal(t_scene *scene, t_mesh_info *info, t_type type)
{
	int			start_mesh;
	t_raw_model	model;

	(void)type;
	start_mesh = scene->mesh_count;
	if (mesh_cache_has(info->path))
	{
		if (!mesh_cache_restore(info->path, scene))
			return (false);
	}
	else
	{
		/* Object layer handles the transformed creation */
		if (!load_injected_mesh(info->path, &model, info->transform,
						info->color, info->emission))
			return (false);
		/* Scene layer handles only addition of the pre-processed model */
		if (!scene_add_raw_model(scene, model))
			return (false);
		mesh_cache_save(info->path, scene, start_mesh);
	}
	if (scene->mesh_count > start_mesh)
		scene_add_group_for_subs(scene, info->path, start_mesh);
	free(info->path);
	return (true);
}
