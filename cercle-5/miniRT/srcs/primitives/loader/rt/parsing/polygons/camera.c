/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:17:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_camera(t_scene *scene, t_camera camera)
{
	scene->camera = camera;
	return (true);
}

bool	parse_camera(t_scene *scene, t_parser *p)
{
	t_camera	cam;
	t_vec3		forward;

	ft_memset(&cam, 0, sizeof(t_camera));
	if (!parse_vec3(p, &cam.transform.pos))
		return (false);
	if (!parse_vec3(p, &forward))
		return (false);
	cam.fov = parse_double(p);
	if (vec3_mag_sq(forward) == 0.0)
		cam.transform.forward = vec3(0, 0, -1);
	else
		cam.transform.forward = vec3_norm(forward);
	return (scene_add_camera(scene, cam));
}
