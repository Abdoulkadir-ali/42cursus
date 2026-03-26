/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_rect(t_scene *scene, t_rect rect)
{
	int	mat_id;

	mat_id = scene_add_material(scene, rect.temp_color);
	if (mat_id < 0)
		return (false);
	rect.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->rects, &scene->rect_count,
			&scene->rect_cap, sizeof(t_rect)))
		return (false);
	scene->rects[scene->rect_count++] = rect;
	return (true);
}