/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_rect(t_scene *scene, t_rect rect)
{
	if (!DYNARRAY_ENSURE_INT(&scene->rects, &scene->rect_count,
			&scene->rect_cap, sizeof(t_rect)))
		return (false);
	if (vec3_mag_sq(rect.transform.scale) < SCALE_EPSILON)
		rect.transform.scale = vec3(1, 1, 1);
	scene->rects[scene->rect_count++] = rect;
	return (true);
}