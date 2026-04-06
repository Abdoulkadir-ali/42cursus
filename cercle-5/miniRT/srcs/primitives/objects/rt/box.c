/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:54:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:19:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_box(t_scene *scene, t_box box)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, box.temp_color);
	if (mat_id.error)
		return (false);
	box.mat_id = mat_id.i;
	if (!DYNARRAY_ENSURE_INT(&scene->boxes, &scene->box_count,
			&scene->box_cap, sizeof(t_box)))
		return (false);
box.mat_slots[0] = box.mat_id;
box.mat_slots[1] = scene->mat_slot_checker;
box.mat_slots[2] = scene->mat_slot_solid;
box.mat_slots[3] = 0;
box.active_slot = 0;
	scene->boxes[scene->box_count++] = box;
	return (true);
}
