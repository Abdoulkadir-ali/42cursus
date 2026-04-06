/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:50:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:19:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_ray	build_hover_ray(t_gui *gui)
{
	t_ray	ray;
	double	w;
	double	h;
	double	half_h;
	double	half_w;

	w = gui->win.size.x;
	h = gui->win.size.y;
	half_h = tan(gui->scene->camera.fov * 0.5 * 3.14159 / 180.0);
	half_w = half_h * (w / h);
	ray.origin = gui->scene->camera.transform.pos;
	ray.direction.x = (2 * (gui->input.mouse.x + 0.5) / w - 1) * half_w;
	ray.direction.y = (1 - 2 * (gui->input.mouse.y + 0.5) / h) * half_h;
	ray.direction.z = 1;
	ray.direction = vec3_norm(mat4_mul_dir(
				mat4_rotation(gui->scene->camera.transform.rotation),
				ray.direction));
	ray_init(&ray, ray.origin, ray.direction);
	return (ray);
}

static void	apply_hover_hit(t_gui *gui, t_hit *hit)
{
	gui->selection.active = true;
	gui->selection.type = hit->ref.type;
	gui->selection.index = init_index(hit->ref.index, false);
}

void	gui_hover(t_gui *gui)
{
	t_ray	ray;
	t_hit	hit;

	if (!gui || !gui->scene)
		return ;
	ray = build_hover_ray(gui);
	hit.t = 1e30;
	hit.hit = false;
	if (bvh_intersect(gui->scene->bvh, &ray, &hit))
		apply_hover_hit(gui, &hit);
	else
		gui->selection.active = false;
}
