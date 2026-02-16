/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

#include "raytracing.h"
#include "physics.h"
#include <math.h>

static void shoot_force(t_gui *gui, int x, int y)
{
	t_ray	ray;
	double	scale;
	double	aspect;
	double	px, py;
	t_vec3	dir;

	if (!gui->scene) return;

	/* 1. Generate Camera Ray */
	scale = tan(gui->cam_ctrl.camera->fov * M_PI / 360.0);
	aspect = (double)gui->win.width / (double)gui->win.height;
	px = (2.0 * (x + 0.5) / gui->win.width - 1.0) * scale * aspect;
	py = (1.0 - 2.0 * (y + 0.5) / gui->win.height) * scale;

	dir = vec3_add(gui->cam_ctrl.transform.forward,
			vec3_add(vec3_scale(gui->cam_ctrl.transform.right, px),
					 vec3_scale(gui->cam_ctrl.transform.up, py)));
	dir = vec3_norm(dir);
	
	ray_init(&ray, gui->cam_ctrl.transform.pos, dir);

	/* 2. Delegate to Physics Engine */
	physics_shoot_ray(gui->scene, ray, 10.0);
}

static void	handle_scroll(int button, t_gui *gui)
{
	if (button == Button4)
	{
		gui->cam_ctrl.target_fov -= ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
	else if (button == Button5)
	{
		gui->cam_ctrl.target_fov += ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
}

int	mouse_click(int button, int x, int y, t_gui *gui)
{
	// Widget engine mouse handling
	widget_handle_mouse(gui, button, x, y);
	if (button == Button1)
	{
		gui->cam_ctrl.mouse_left_pressed = true;
		gui->cam_ctrl.last_mouse_x = x;
		gui->cam_ctrl.last_mouse_y = y;
	}
	else if (button == Button2)
	{
		gui->cam_ctrl.mouse_middle_pressed = true;
		gui->cam_ctrl.last_mouse_x = x;
		gui->cam_ctrl.last_mouse_y = y;
	}
	else if (button == 3) /* Right Click */
	{
		shoot_force(gui, x, y);
	}
	else
		handle_scroll(button, gui);
	return (0);
}

int	mouse_release(int button, int x, int y, t_gui *gui)
{
	(void)x;
	(void)y;
	if (button == Button1)
		gui->cam_ctrl.mouse_left_pressed = false;
	else if (button == Button2)
		gui->cam_ctrl.mouse_middle_pressed = false;
	return (0);
}
