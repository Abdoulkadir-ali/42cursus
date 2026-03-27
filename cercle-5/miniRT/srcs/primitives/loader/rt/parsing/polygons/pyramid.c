/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:22:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_pyramid(t_scene *scene, t_pyramid pyramid)
{
	if (!DYNARRAY_ENSURE_INT(&scene->pyramids, &scene->pyramid_count,
			&scene->pyramid_cap, sizeof(t_pyramid)))
		return (false);
	if (vec3_mag_sq(pyramid.transform.scale) < SCALE_EPSILON)
		pyramid.transform.scale = vec3(1, 1, 1);
	scene->pyramids[scene->pyramid_count++] = pyramid;
	return (true);
}

bool	parse_pyramid(t_scene *scene, t_parser *p)
{
	t_pyramid	py;
	t_vec3		color;

	ft_memset(&py, 0, sizeof(t_pyramid));
	if (!parse_vec3(p, &py.transform.pos) || !parse_vec3(p, &py.up))
		return (false);
	py.base_size = parse_double(p);
	py.height = parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	py.up = vec3_norm(py.up);
	py.mat_id = scene_add_material(scene, color);
	if (py.mat_id < 0)
		return (false);
	return (scene_add_pyramid(scene, py));
}
