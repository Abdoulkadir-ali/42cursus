/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 20:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/* Clamps pitch to avoid gimbal lock/flipping. */
void	camera_rotate_pitch(t_gui *gui, double delta_pitch)
{
	gui->cam_ctrl.target_rot.pitch += delta_pitch;
	if (gui->cam_ctrl.target_rot.pitch > M_PI / 2)
		gui->cam_ctrl.target_rot.pitch = M_PI / 2;
	if (gui->cam_ctrl.target_rot.pitch < -M_PI / 2)
		gui->cam_ctrl.target_rot.pitch = -M_PI / 2;
}

/* Rotates the camera yaw (horizontal rotation). */
void	camera_rotate_yaw(t_gui *gui, double delta_yaw)
{
	gui->cam_ctrl.target_rot.yaw += delta_yaw;
	while (gui->cam_ctrl.target_rot.yaw > M_PI)
		gui->cam_ctrl.target_rot.yaw -= 2 * M_PI;
	while (gui->cam_ctrl.target_rot.yaw < -M_PI)
		gui->cam_ctrl.target_rot.yaw += 2 * M_PI;
}
