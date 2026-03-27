/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_pyramid(t_scene *scene, t_pyramid pyramid)
{
	if (!DYNARRAY_ENSURE_INT(&scene->pyramids, &scene->pyramid_count,
			&scene->pyramid_cap, sizeof(t_pyramid)))
		return (false);
	if (vec3_mag_sq(pyramid.transform.scale) < SCALE_EPSILON)
		pyramid.transform.scale = vec3(1, 1, 1);
	scene->pyramids[scene->pyramid_count++] = pyramid;
	return (true);
}
