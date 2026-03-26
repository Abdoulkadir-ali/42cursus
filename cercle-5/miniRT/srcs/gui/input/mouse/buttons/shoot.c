/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:26:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "physics.h"

void	shoot_force(t_gui *gui, t_vec2i mouse)
{
	t_ray	 ray;
	double	 scale;
	double	 aspect;
	t_vec2	 p;
	t_vec3	 dir;

	if (!gui->scene)
		return ;
	scale = tan(gui->cam_ctrl.camera->fov * M_PI / 360.0);
	aspect = (double)gui->win.width / (double)gui->win.height;
	p.x = (2.0 * (mouse.x + 0.5) / gui->win.width - 1.0) * scale * aspect;
	p.y = (1.0 - 2.0 * (mouse.y + 0.5) / gui->win.height) * scale;
	dir = vec3_add(gui->cam_ctrl.transform.forward,
			vec3_add(vec3_scale(gui->cam_ctrl.transform.right, p.x),
				vec3_scale(gui->cam_ctrl.transform.up, p.y)));
	dir = vec3_norm(dir);
	ray_init(&ray, gui->cam_ctrl.transform.pos, dir);
	physics_shoot_ray(gui->scene, ray, 10.0);
}
