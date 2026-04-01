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

void	get_forward(double pitch, double yaw, t_vec3 *out)
{
	*out = vec3_norm(vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch)
				* cos(yaw)));
}

void	apply_movement(t_camera_controller *ctrl, t_vec3 fwd, t_vec3 right)
{
	t_vec3	up;
	double	speed;

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
