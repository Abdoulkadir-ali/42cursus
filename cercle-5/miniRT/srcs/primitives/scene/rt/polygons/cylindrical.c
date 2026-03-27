/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindrical.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_cylinder(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_cylinder_obj(p);
	if (parsed.type != TYPE_CYLINDER)
		return (false);
	parsed.data.cylinder.mat_id = scene_add_material(scene,
			parsed.data.cylinder.temp_color);
	if (parsed.data.cylinder.mat_id < 0)
		return (false);
	return (scene_add_cylinder(scene, parsed.data.cylinder));
}

bool	parse_cone(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_cone_obj(p);
	if (parsed.type != TYPE_CONE)
		return (false);
	parsed.data.cone.mat_id = scene_add_material(scene,
			parsed.data.cone.temp_color);
	if (parsed.data.cone.mat_id < 0)
		return (false);
	return (scene_add_cone(scene, parsed.data.cone));
}
