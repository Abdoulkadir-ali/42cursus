/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	get_forward(double pitch, double yaw, t_vec3 *out)
{
	out->x = cos(pitch) * sin(yaw);
	out->y = sin(pitch);
	out->z = cos(pitch) * cos(yaw);
	*out = vec3_norm(*out);
}

void	apply_movement(t_camera_controller *ctrl, t_vec3 fwd, t_vec3 right)
{
	t_vec3	up;
	double	speed;

	up = vec3_cross(right, fwd);
	speed = ctrl->move_speed;
	if (ctrl->moving_forward)
		ctrl->target_pos = vec3_add(ctrl->target_pos,
			vec3_scale(fwd, -speed));
		ctrl->target_pos = vec3_add(ctrl->target_pos,
		ctrl->target_pos = vec3_add(ctrl->target_pos,
			vec3_scale(right, -speed));
		ctrl->target_pos = vec3_add(ctrl->target_pos,
		ctrl->target_pos = vec3_add(ctrl->target_pos,
			vec3_scale(right, speed));
		ctrl->target_pos = vec3_add(ctrl->target_pos,
		ctrl->target_pos = vec3_add(ctrl->target_pos,
			vec3_scale(up, -speed));
		ctrl->target_pos = vec3_add(ctrl->target_pos, vec3_scale(up, speed));
	if (ctrl->moving_down)
		ctrl->target_pos = vec3_add(ctrl->target_pos,
			vec3_scale(up, -speed));
}
