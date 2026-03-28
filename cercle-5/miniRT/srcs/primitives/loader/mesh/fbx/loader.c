/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:04:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 04:11:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Injects the pre-parsed FBX assets into the scene's DOD structures.
 */
static bool	scene_add_fbx(t_scene *scene, t_fbx *fbx)
{
	int		i;

	i = 0;
	while (i < fbx->mesh_count)
		scene_add_mesh(scene, fbx->meshes[i++]);
	i = 0;
	while (i < fbx->anim_count)
		scene_add_animation(scene, fbx->animations[i++]);
	return (true);
}

/**
 * @brief FBX parsing entry point. Detects format and populates the scene.
 */
bool	parse_fbx(t_scene *scene, t_parser *p)
{
	t_fbx	fbx;
	bool	res;

	ft_memset(&fbx, 0, sizeof(t_fbx));
	fbx.path = p->path;
	fbx.fd = p->fd;
	if (fbx_is_binary(p->fd))
		res = fbx_parse_binary(&fbx);
	else
		res = fbx_parse_ascii(&fbx);
	if (res == true)
		res = scene_add_fbx(scene, &fbx);
	fbx_clear_asset(&fbx);
	return (res);
}
