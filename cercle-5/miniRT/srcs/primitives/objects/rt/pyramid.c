/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:54:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:19:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_pyramid(t_scene *scene, t_pyramid py)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, py.temp_color);
	if (mat_id.error)
		return (false);
	py.mat_id = mat_id.i;
	if (!DYNARRAY_ENSURE_INT(&scene->pyramids, &scene->pyramid_count,
			&scene->pyramid_cap, sizeof(t_pyramid)))
		return (false);
py.mat_slots[0] = py.mat_id;
py.mat_slots[1] = scene->mat_slot_checker;
py.mat_slots[2] = scene->mat_slot_solid;
py.mat_slots[3] = 0;
py.active_slot = 0;
	scene->pyramids[scene->pyramid_count++] = py;
	return (true);
}
