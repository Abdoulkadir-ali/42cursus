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

bool	scene_add_pyramid(t_scene *scene, t_pyramid py)
{
	int	mat_id;

	mat_id = scene_add_material(scene, py.temp_color);
	if (mat_id < 0)
		return (false);
	py.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->pyramids, &scene->pyramid_count,
			&scene->pyramid_cap, sizeof(t_pyramid)))
		return (false);
	scene->pyramids[scene->pyramid_count++] = py;
	return (true);
}
