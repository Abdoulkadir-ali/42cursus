/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:25:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 19:25:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "physics.h"
#include "raytracing.h"

static void	shoot_force(t_gui *gui, t_vec2i mouse)
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

static int	mlx_mouse_click(int button, int x, int y, t_gui *gui)
{
	return (mouse_click(button, vec2i(x, y), gui));
}

int	(*mouse_click_hook(void))(int, int, int, t_gui *)
{
	return (mlx_mouse_click);
}

static int	mlx_mouse_release(int button, int x, int y, t_gui *gui)
{
	return (mouse_release(button, vec2i(x, y), gui));
}

int	(*mouse_release_hook(void))(int, int, int, t_gui *)
{
	return (mlx_mouse_release);
}

int	mouse_click(int button, t_vec2i mouse, t_gui *gui)
{
	widget_handle_mouse(gui, button, mouse);
	if (button == BUTTON_LEFT)
	{
		gui->cam_ctrl.mouse_left_pressed = true;
		gui->cam_ctrl.last_mouse = mouse;
	}
	else if (button == BUTTON_MIDDLE)
	{
		gui->cam_ctrl.mouse_middle_pressed = true;
		gui->cam_ctrl.last_mouse = mouse;
	}
	else if (button == BUTTON_RIGHT)
		shoot_force(gui, mouse);
	else
		handle_scroll(button, gui);
	return (0);
}

int	mouse_release(int button, t_vec2i mouse, t_gui *gui)
{
	(void)mouse;
	if (button == BUTTON_LEFT)
		gui->cam_ctrl.mouse_left_pressed = false;
	else if (button == BUTTON_MIDDLE)
		gui->cam_ctrl.mouse_middle_pressed = false;
	return (0);
}
