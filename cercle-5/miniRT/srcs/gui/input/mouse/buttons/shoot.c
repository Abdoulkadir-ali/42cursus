/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 02:31:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	shoot_force(t_gui *gui, t_vec2i mouse)
{
	t_ray	ray;
	double	scale;
	double	aspect;
	t_vec2	p;
	t_vec3	dir;

	if (!gui || !gui->scene || !gui->cam_ctrl.camera)
		return ;
	scale = tan(gui->cam_ctrl.camera->fov * M_PI / 360.0);
	aspect = (double)gui->win.size.x / (double)gui->win.size.y;
	p.x = (double)mouse.x * gui->win.size.x / gui->win.disp_size.x;
	p.y = (double)mouse.y * gui->win.size.y / gui->win.disp_size.y;
	p.x = (2.0 * (p.x + 0.5) / gui->win.size.x - 1.0) * scale * aspect;
	p.y = (1.0 - 2.0 * (p.y + 0.5) / gui->win.size.y) * scale;
	dir = vec3_add(gui->cam_ctrl.transform.forward,
			vec3_add(vec3_scale(gui->cam_ctrl.transform.right, p.x),
				vec3_scale(gui->cam_ctrl.transform.up, p.y)));
	dir = vec3_norm(dir);
	ray_init(&ray, gui->cam_ctrl.transform.pos, dir);
	physics_shoot_ray(gui->scene, ray, 10.0);
	gui->render.dirty = true;
}
