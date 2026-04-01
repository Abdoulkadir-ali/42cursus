/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:54:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 21:21:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_box(t_scene *scene, t_box box)
{
	int	mat_id;

	mat_id = scene_add_material(scene, box.temp_color);
	if (mat_id < 0)
		return (false);
	box.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->boxes, &scene->box_count,
			&scene->box_cap, sizeof(t_box)))
		return (false);
	scene->boxes[scene->box_count++] = box;
	return (true);
}
