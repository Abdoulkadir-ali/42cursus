/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_plane(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_plane_obj(p);
	if (parsed.type != TYPE_PLANE)
		return (false);
	parsed.data.plane.mat_id = scene_add_material(scene,
			parsed.data.plane.temp_color);
	if (parsed.data.plane.mat_id < 0)
		return (false);
	return (scene_add_plane(scene, parsed.data.plane));
}
