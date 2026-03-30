/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:39:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 21:52:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	setup_default_scene(t_scene *scene)
{
	t_light	light;

	scene->ambient.brightness = 0.2;
	scene->ambient.rgb = vec3(255, 255, 255);
	scene->camera.fov = 70.0;
	scene->camera.transform.pos = vec3(0, 2, -5);
	scene->camera.transform.forward = vec3(0, 0, 1);
	scene->camera.transform.up = vec3(0, 1, 0);
	scene->camera.transform.right = vec3(1, 0, 0);
	scene->camera.transform.scale = vec3(1, 1, 1);
	ft_memset(&light, 0, sizeof(light));
	light.type = LIGHT_POINT;
	light.transform.pos = vec3(0, 10, -5);
	light.transform.scale = vec3(1, 1, 1);
	light.brightness = 0.8;
	light.rgb = vec3(255, 255, 255);
	scene_add_light(scene, light);
}

