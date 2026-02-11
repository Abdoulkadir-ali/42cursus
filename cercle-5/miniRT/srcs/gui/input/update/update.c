/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	get_forward(double pitch, double yaw, t_vec3 *out);
void	apply_movement(t_camera_controller *ctrl, t_vec3 fwd, t_vec3 right);
void	smooth_rotation(t_gui *gui, t_camera_controller *ctrl);
void	smooth_position(t_gui *gui, t_camera_controller *ctrl);
void	update_fov(t_gui *gui, t_camera_controller *ctrl);

void	gui_update_input(t_gui *gui)
{
	t_camera_controller	*ctrl;
	t_vec3				fwd;
	t_vec3				right;

	ctrl = &gui->cam_ctrl;
	if (!ctrl->camera)
		return ;
	get_forward(ctrl->transform.rotation.pitch,
		ctrl->transform.rotation.yaw, &fwd);
	right = vec3_norm(vec3_cross(fwd, vec3(0, 1, 0)));
	if (vec3_mag_sq(right) < 1e-6)
		right = vec3(1, 0, 0);
	apply_movement(ctrl, fwd, right);
	smooth_rotation(gui, ctrl);
	smooth_position(gui, ctrl);
	ctrl->camera->transform = ctrl->transform;
	update_fov(gui, ctrl);
	if (gui->render.dirty)
		gui->render.scale = 2;
	else
		gui->render.scale = 1;
}
