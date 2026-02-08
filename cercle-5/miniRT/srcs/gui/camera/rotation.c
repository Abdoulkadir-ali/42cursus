/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/04 02:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	camera_rotate_yaw(t_gui *gui, double delta_yaw)
{
	gui->rotation.yaw += delta_yaw;
	// Keep yaw in -pi to pi
	while (gui->rotation.yaw > M_PI)
		gui->rotation.yaw -= 2 * M_PI;
	while (gui->rotation.yaw < -M_PI)
		gui->rotation.yaw += 2 * M_PI;
}

void	camera_rotate_pitch(t_gui *gui, double delta_pitch)
{
	gui->rotation.pitch += delta_pitch;
	// Clamp pitch to avoid gimbal lock
	if (gui->rotation.pitch > M_PI / 2)
		gui->rotation.pitch = M_PI / 2;
	if (gui->rotation.pitch < -M_PI / 2)
		gui->rotation.pitch = -M_PI / 2;
}