/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_tri_shape(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_tri_shape_obj(p);
	if (parsed.type != TYPE_TRI)
		return (false);
	parsed.data.tri_shape.mat_id = scene_add_material(scene,
			parsed.data.tri_shape.temp_color);
	if (parsed.data.tri_shape.mat_id < 1)
		return (false);
	return (scene_add_tri(scene, parsed.data.tri_shape));
}

bool	parse_rect(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_rect_obj(p);
	if (parsed.type != TYPE_RECT)
		return (false);
	parsed.data.rect.mat_id = scene_add_material(scene,
			parsed.data.rect.temp_color);
	if (parsed.data.rect.mat_id < 1)
		return (false);
	return (scene_add_rect(scene, parsed.data.rect));
}

bool	parse_pyramid(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_pyramid_obj(p);
	if (parsed.type != TYPE_PYRAMID)
		return (false);
	parsed.data.pyramid.mat_id = scene_add_material(scene,
			parsed.data.pyramid.temp_color);
	if (parsed.data.pyramid.mat_id < 1)
		return (false);
	return (scene_add_pyramid(scene, parsed.data.pyramid));
}
