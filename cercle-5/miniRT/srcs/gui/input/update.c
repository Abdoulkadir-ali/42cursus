/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#    +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static t_vec3	get_fwd(double pitch, double yaw)
{
	t_vec3	dir;

	dir.x = cos(pitch) * sin(yaw);
	dir.y = sin(pitch);
	dir.z = cos(pitch) * cos(yaw);
	return (vec3_norm(dir));
}

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

static void	update_fov(t_gui *gui, t_camera_controller *ctrl)
{
	if (ctrl->zooming_in)
	{
		ctrl->target_fov -= 1.0;
		clamp_fov(&ctrl->target_fov);
	}
	if (ctrl->zooming_out)
	{
		ctrl->target_fov += 1.0;
		clamp_fov(&ctrl->target_fov);
	}
	if (fabs(ctrl->target_fov - ctrl->camera->fov) > 1e-2)
	{
		ctrl->camera->fov += (ctrl->target_fov - ctrl->camera->fov)
			* ctrl->lerp_factor;
		gui->render.dirty = true;
	}
}

void	gui_update_input(t_gui *gui)
{
	t_camera_controller	*ctrl;
	t_vec3				fwd;
	t_vec3				right;

	ctrl = &gui->cam_ctrl;
	if (!ctrl->camera)
		return ;
	fwd = get_fwd(ctrl->transform.rotation.pitch, ctrl->transform.rotation.yaw);
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
