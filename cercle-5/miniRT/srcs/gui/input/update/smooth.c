/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	smooth_rotation(t_gui *gui, t_camera_controller *ctrl)
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

void	smooth_position(t_gui *gui, t_camera_controller *ctrl)
{
	t_vec3	pos_diff;

	pos_diff = vec3_sub(ctrl->target_pos, ctrl->transform.pos);
	if (vec3_mag_sq(pos_diff) > 1e-6)
	{
		ctrl->transform.pos = vec3_add(ctrl->transform.pos,
				vec3_scale(pos_diff, ctrl->lerp_factor));
		gui->render.dirty = true;
	}
}
