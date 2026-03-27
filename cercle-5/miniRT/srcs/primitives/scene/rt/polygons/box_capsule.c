/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_capsule.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_box(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_box_obj(p);
	if (parsed.type != TYPE_BOX)
		return (false);
	parsed.data.box.mat_id = scene_add_material(scene,
			parsed.data.box.temp_color);
	return (scene_add_box(scene, parsed.data.box));
}

bool	parse_capsule(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_capsule_obj(p);
	if (parsed.type != TYPE_CAPSULE)
		return (false);
	parsed.data.capsule.mat_id = scene_add_material(scene,
			parsed.data.capsule.temp_color);
	return (scene_add_capsule(scene, parsed.data.capsule));
}
