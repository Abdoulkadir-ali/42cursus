/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "optimizations.h"

static void	update_ctrl_transform(t_camera_controller *ctrl, t_vec3 fwd,
	t_vec3 right, t_vec3 up)
{
	ctrl->transform.forward = fwd;
	ctrl->transform.right = right;
	ctrl->transform.up = up;
	ctrl->camera->transform = ctrl->transform;
}

static void	get_basis(t_camera_controller *ctrl, t_vec3 *fwd, t_vec3 *right,
	t_vec3 *up)
{
	get_forward(ctrl->transform.rotation.pitch, ctrl->transform.rotation.yaw,
		fwd);
	*right = vec3_norm(vec3_cross(*fwd, vec3(0, 1, 0)));
	if (vec3_mag_sq(*right) < 1e-6)
		*right = vec3(1, 0, 0);
	*up = vec3_norm(vec3_cross(*right, *fwd));
}

void	gui_update_input(t_gui *gui)
{
	t_camera_controller	*ctrl;
	t_vec3				fwd;
	t_vec3				right;
	t_vec3				up;

	ctrl = &gui->cam_ctrl;
	if (!ctrl->camera)
		return ;
	get_basis(ctrl, &fwd, &right, &up);
	update_ctrl_transform(ctrl, fwd, right, up);
	apply_movement(ctrl, fwd, right);
	smooth_rotation(gui, ctrl);
	smooth_position(gui, ctrl);
	update_fov(gui, ctrl);
	if (gui->render.force_fullres)
		gui->render.scale = SCALE_MIN;
}
