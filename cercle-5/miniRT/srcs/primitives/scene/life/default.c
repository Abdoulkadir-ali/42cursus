/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:39:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 21:57:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	add_default_light(t_scene *scene, t_vec3 pos, t_vec3 rgb)
{
	t_light	light;

	ft_memset(&light, 0, sizeof(light));
	light.type = LIGHT_POINT;
	light.transform.pos = pos;
	light.transform.scale = vec3(1, 1, 1);
	light.brightness = 0.8;
	light.rgb = rgb;
	scene_add_light(scene, light);
}

static void	add_ground_plane(t_scene *scene)
{
	t_plane	pl;

	ft_memset(&pl, 0, sizeof(pl));
	pl.transform.pos = vec3(0, 0, 0);
	pl.transform.forward = vec3(0, 1, 0);
	pl.transform.up = vec3(0, 0, 1);
	pl.transform.right = vec3(1, 0, 0);
	pl.transform.scale = vec3(1, 1, 1);
	pl.temp_color = vec3(150, 150, 150);
	scene_add_plane(scene, pl);
}

void	setup_default_scene(t_scene *scene)
{
	scene->ambient.brightness = 0.3;
	scene->ambient.rgb = vec3(255, 255, 255);
	scene->camera.fov = 70.0;
	scene->camera.transform.pos = vec3(0, 0, 1);
	scene->camera.transform.forward = vec3(0, 0, -1);
	scene->camera.transform.up = vec3(0, 1, 0);
	scene->camera.transform.right = vec3(1, 0, 0);
	scene->camera.transform.scale = vec3(1, 1, 1);
	add_default_light(scene, vec3(-30, 200, 30), vec3(255, 255, 255));
	add_default_light(scene, vec3(-15, 40, 10), vec3(100, 50, 30));
	add_default_light(scene, vec3(0, 60, -20), vec3(100, 50, 30));
	add_ground_plane(scene);
}
