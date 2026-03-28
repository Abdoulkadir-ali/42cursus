/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 18:04:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief DOD Transition of GLB assets into the active scene.
 * This is the static core of the transition layer.
 */
static bool	scene_add_glb(t_scene *scene, t_glb *glb)
{
	t_json_value	*ms;
	int				*map;
	int				c;
	size_t			i;

	c = 0;
	map = glb_inject_materials(scene, glb, &c);
	ms = json_get(glb->json, "meshes");
	if (ms == NULL || ms->type != JSON_ARRAY)
	{
		if (map != NULL)
			free(map);
		return (true);
	}
	i = 0;
	while (i < ms->array.count)
		glb_inject_mesh_atomic(scene, glb, json_get(json_at(ms, i++),
						"primitives"), map);
	if (map != NULL)
		free(map);
	return (true);
}

/**
 * @brief Specialized GLB parsing entrance.
 * Calls the orchestrated parsing logic and then finalizes in the scene.
 */
bool	parse_glb(t_scene *scene, t_parser *p)
{
	t_glb	glb;
	bool	res;

	if (glb_parse_to_asset(&glb, p->fd, p->path) == false)
		return (false);
	res = scene_add_glb(scene, &glb);
	json_free(glb.json);
	free(glb.bin_ref); /* Or whatever bin buffer was in glb */
	if (glb.materials != NULL)
		free(glb.materials);
	if (glb.animations != NULL)
		free(glb.animations);
	return (res);
}
