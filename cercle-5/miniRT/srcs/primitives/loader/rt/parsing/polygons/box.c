/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:21:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_box(t_scene *scene, t_box box)
{
	if (!DYNARRAY_ENSURE_INT(&scene->boxes, &scene->box_count,
			&scene->box_cap, sizeof(t_box)))
		return (false);
	if (vec3_mag_sq(box.transform.scale) < SCALE_EPSILON)
		box.transform.scale = vec3(1, 1, 1);
	scene->boxes[scene->box_count++] = box;
	return (true);
}

bool	parse_box(t_scene *scene, t_parser *p)
{
	t_box	box;
	t_vec3	color;

	ft_memset(&box, 0, sizeof(t_box));
	if (!parse_vec3(p, &box.transform.pos))
		return (false);
	if (!parse_vec3(p, &box.half_extents))
		return (false);
	if (!parse_vec3(p, &color))
		return (false);
	box.mat_id = scene_add_material(scene, color);
	return (scene_add_box(scene, box));
}

