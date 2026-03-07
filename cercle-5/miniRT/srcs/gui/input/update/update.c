/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2026/02/11 16:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	gui_update_input(t_gui *gui)
{
	t_camera_controller *ctrl;
	t_vec3 fwd;
	t_vec3 right;

	ctrl = &gui->cam_ctrl;
	if (!ctrl->camera)
		return ;
	get_forward(ctrl->transform.rotation.pitch, ctrl->transform.rotation.yaw,
		&fwd);
	right = vec3_norm(vec3_cross(fwd, vec3(0, 1, 0)));
	if (vec3_mag_sq(right) < 1e-6)
		right = vec3(1, 0, 0);
	t_vec3 up = vec3_norm(vec3_cross(right, fwd));
	ctrl->transform.forward = fwd;
	ctrl->transform.right = right;
	ctrl->transform.up = up;

	apply_movement(ctrl, fwd, right);
	smooth_rotation(gui, ctrl);
	smooth_position(gui, ctrl);
	ctrl->camera->transform = ctrl->transform;
	update_fov(gui, ctrl);
	if (ctrl->moving_forward || ctrl->moving_backward
		|| ctrl->moving_left || ctrl->moving_right
		|| ctrl->moving_up || ctrl->moving_down
		|| ctrl->zooming_in || ctrl->zooming_out
		|| ctrl->mouse_left_pressed || ctrl->mouse_middle_pressed)
		gui->render.scale = 2;
	else
		gui->render.scale = 1;
}
