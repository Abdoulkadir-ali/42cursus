/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:50:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:50:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void gui_hover(t_gui *gui)
{
	t_ray ray;
	t_hit hit;
	double aspect_ratio;
	double half_height;
	double half_width;

	if (!gui || !gui->scene)
		return ;
	aspect_ratio = (double)gui->win.size.x / (double)gui->win.size.y;
	half_height = tan(gui->scene->camera.fov * 0.5 * 3.14159 / 180.0);
	half_width = half_height * aspect_ratio;
	
	ray.origin = gui->scene->camera.transform.pos;
	ray.direction.x = (2 * (gui->input.mouse.x + 0.5) / (double)gui->win.size.x - 1) * half_width;
	ray.direction.y = (1 - 2 * (gui->input.mouse.y + 0.5) / (double)gui->win.size.y) * half_height;
	ray.direction.z = 1;
	ray.direction = vec3_norm(mat4_mul_dir(mat4_rotation(gui->scene->camera.transform.rotation), 
					ray.direction));
	ray_init(&ray, ray.origin, ray.direction);
	
	hit.t = 1e30;
	hit.hit = false;
	if (bvh_intersect(gui->scene->bvh, &ray, &hit))
	{
		gui->selection.active = true;
		gui->selection.type = hit.ref.type;
		gui->selection.index = hit.ref.index;
	}
	else
		gui->selection.active = false;
}
