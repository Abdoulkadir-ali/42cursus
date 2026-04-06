/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:46:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:46:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_tri(t_scene *scene, t_tri_shape tri)
{
	t_index	mat_id;

	mat_id = scene_add_material(scene, tri.temp_color);
	if (mat_id.error)
		return (false);
	tri.mat_id = mat_id.i;
	if (!DYNARRAY_ENSURE_INT(&scene->tris, &scene->tri_count,
			&scene->tri_cap, sizeof(t_tri_shape)))
		return (false);
tri.mat_slots[0] = tri.mat_id;
tri.mat_slots[1] = scene->mat_slot_checker;
tri.mat_slots[2] = scene->mat_slot_solid;
tri.mat_slots[3] = 0;
tri.active_slot = 0;
	scene->tris[scene->tri_count++] = tri;
	return (true);
}
