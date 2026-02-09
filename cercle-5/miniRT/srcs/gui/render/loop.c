/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 16:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Returns current time in milliseconds.
*/
static long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

/*
** Updates camera position based on input flags.
*/
static void	apply_movement(t_gui *gui, t_camera_controller *ctrl, t_vec3 fwd,
		t_vec3 right)
{
	t_vec3	up;
	double	speed;

	(void)gui;
	up = vec3_cross(right, fwd);
	speed = ctrl->move_speed;
	if (ctrl->moving_forward)
		ctrl->target_pos = vec3_add(ctrl->target_pos, vec3_scale(fwd, speed));
	if (ctrl->moving_backward)
		ctrl->target_pos = vec3_add(ctrl->target_pos, vec3_scale(fwd, -speed));
	if (ctrl->moving_left)
		ctrl->target_pos = vec3_add(ctrl->target_pos, vec3_scale(right,
					-speed));
	if (ctrl->moving_right)
		ctrl->target_pos = vec3_add(ctrl->target_pos, vec3_scale(right, speed));
	if (ctrl->moving_up)
		ctrl->target_pos = vec3_add(ctrl->target_pos, vec3_scale(up, speed));
	if (ctrl->moving_down)
		ctrl->target_pos = vec3_add(ctrl->target_pos, vec3_scale(up, -speed));
}

/*
** Applies smooth interpolation to camera rotation.
*/
static void	smooth_rotation(t_gui *gui, t_camera_controller *ctrl)
{
	double	diff_yaw;
	double	diff_pitch;

	diff_yaw = ctrl->target_rot.yaw - ctrl->transform.rotation.yaw;
	diff_pitch = ctrl->target_rot.pitch - ctrl->transform.rotation.pitch;
	if (fabs(diff_yaw) > 1e-4 || fabs(diff_pitch) > 1e-4)
	{
		ctrl->transform.rotation.yaw += diff_yaw * ctrl->lerp_factor;
		ctrl->transform.rotation.pitch += diff_pitch * ctrl->lerp_factor;
		gui->render.dirty = true;
	}
}

/*
** Applies smooth interpolation to camera position.
*/
static void	smooth_position(t_gui *gui, t_camera_controller *ctrl)
{
	t_vec3	pos_diff;

	pos_diff = vec3_sub(ctrl->target_pos, ctrl->transform.pos);
	if (vec3_mag_sq(pos_diff) > 1e-6)
	{
		ctrl->transform.pos = vec3_add(ctrl->transform.pos, vec3_scale(pos_diff,
					ctrl->lerp_factor));
		gui->render.dirty = true;
	}
}

/*
** Updates FOV based on zoom input and interpolation.
*/
static void	update_fov(t_gui *gui, t_camera_controller *ctrl)
{
	if (ctrl->zooming_in)
	{
		ctrl->target_fov -= 1.0;
		if (ctrl->target_fov < 10)
			ctrl->target_fov = 10;
	}
	if (ctrl->zooming_out)
	{
		ctrl->target_fov += 1.0;
		if (ctrl->target_fov > 170)
			ctrl->target_fov = 170;
	}
	if (fabs(ctrl->target_fov - ctrl->camera->fov) > 1e-2)
	{
		ctrl->camera->fov += (ctrl->target_fov - ctrl->camera->fov)
			* ctrl->lerp_factor;
		gui->render.dirty = true;
	}
}

/*
** Main update function for handling input and camera state.
*/
static void	update_input(t_gui *gui)
{
	t_camera_controller	*ctrl;
	t_vec3				fwd;
	t_vec3				right;

	ctrl = &gui->cam_ctrl;
	if (!ctrl->camera)
		return ;
	fwd = get_camera_forward(ctrl->transform.rotation.pitch,
			ctrl->transform.rotation.yaw);
	right = vec3_norm(vec3_cross(fwd, vec3(0, 1, 0)));
	if (vec3_mag_sq(right) < 1e-6)
		right = vec3(1, 0, 0);
	apply_movement(gui, ctrl, fwd, right);
	smooth_rotation(gui, ctrl);
	smooth_position(gui, ctrl);
	ctrl->camera->transform = ctrl->transform;
	update_fov(gui, ctrl);
	if (gui->render.dirty)
		gui->render.scale = 2;
	else
		gui->render.scale = 1;
}

/*
** Rendering loop callback function.
** Updates input, renders frame if needed, and calculates FPS.
*/
static int	render_loop(void *param)
{
	t_gui		*gui;
	long long	current_time;
	double		delta;
	static bool	last_dirty = false;

	gui = (t_gui *)param;
	current_time = get_time_ms();
	if (gui->render.last_time > 0)
	{
		delta = (current_time - gui->render.last_time) / 1000.0;
		if (delta > 0)
			gui->render.fps = 0.9 * gui->render.fps + 0.1 * (1.0 / delta);
	}
	gui->render.last_time = current_time;
	update_input(gui);
	if (gui->render.dirty || last_dirty)
	{
		gui_render(gui);
		if (!gui->render.dirty)
			last_dirty = false;
		else
			last_dirty = true;
		gui->render.dirty = false;
	}
	return (0);
}

/*
** Starts the main GUI loop.
*/
void	gui_loop(t_gui *gui)
{
	mlx_hook(gui->win.win, KeyPress, KeyPressMask, key_press, gui);
	mlx_hook(gui->win.win, KeyRelease, KeyReleaseMask, key_release, gui);
	mlx_hook(gui->win.win, ButtonPress, ButtonPressMask, mouse_click, gui);
	mlx_hook(gui->win.win, ButtonRelease, ButtonReleaseMask, mouse_release, gui);
	mlx_hook(gui->win.win, MotionNotify, PointerMotionMask, mouse_motion, gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	mlx_loop_hook(gui->win.mlx, (int (*)())render_loop, gui);
	mlx_loop(gui->win.mlx);
}