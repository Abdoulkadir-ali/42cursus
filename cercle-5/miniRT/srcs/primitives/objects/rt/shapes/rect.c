/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:21:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_rect(t_scene *scene, t_rect rect)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, rect.temp_color);
	if (mat_id.error)
		return (false);
	rect.mat_id = mat_id.i;
	if (!DYNARRAY_ENSURE_INT(&scene->rects, &scene->rect_count,
			&scene->rect_cap, sizeof(t_rect)))
		return (false);
	rect.mat_slots[0] = rect.mat_id;
	rect.mat_slots[1] = scene->mat_slot_checker;
	rect.mat_slots[2] = scene->mat_slot_solid;
	rect.mat_slots[3] = 0;
	rect.active_slot = 0;
	scene->rects[scene->rect_count++] = rect;
	return (true);
}
