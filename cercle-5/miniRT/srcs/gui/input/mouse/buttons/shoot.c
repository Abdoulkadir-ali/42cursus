/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:44:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "physics.h"
#include "raytracing.h"

static void	compute_shoot_ray(t_gui *gui, t_vec2i mouse, t_ray *ray)
{
	double	scale;
	double	aspect;
	t_vec2	p;
	t_vec3	dir;

	scale = tan(gui->cam_ctrl.camera->fov * M_PI / 360.0);
	aspect = (double)gui->win.size.x / (double)gui->win.size.y;
	p.x = (2.0 * (mouse.x + 0.5) / gui->win.size.x - 1.0) * scale * aspect;
	p.y = (1.0 - 2.0 * (mouse.y + 0.5) / gui->win.size.y) * scale;
	dir = vec3_add(gui->cam_ctrl.transform.forward,
			vec3_add(vec3_scale(gui->cam_ctrl.transform.right, p.x),
				vec3_scale(gui->cam_ctrl.transform.up, p.y)));
	dir = vec3_norm(dir);
	ray_init(ray, gui->cam_ctrl.transform.pos, dir);
}

void	shoot_force(t_gui *gui, t_vec2i mouse)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	impulse;

	if (!gui->scene || !gui->rt.bvh)
		return ;
	compute_shoot_ray(gui, mouse, &ray);
	ft_memset(&hit, 0, sizeof(t_hit));
	if (!bvh_intersect(gui->rt.bvh, &ray, &hit))
		return ;
	impulse = vec3_scale(ray.direction, 10.0);
	physics_apply_impulse(gui->phys, hit.ref.index, impulse);
}
