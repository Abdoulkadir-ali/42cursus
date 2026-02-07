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
	gui->yaw += delta_yaw;
	// Keep yaw in -pi to pi
	while (gui->yaw > M_PI)
		gui->yaw -= 2 * M_PI;
	while (gui->yaw < -M_PI)
		gui->yaw += 2 * M_PI;
}

void	camera_rotate_pitch(t_gui *gui, double delta_pitch)
{
	gui->pitch += delta_pitch;
	// Clamp pitch to avoid gimbal lock
	if (gui->pitch > M_PI / 2)
		gui->pitch = M_PI / 2;
	if (gui->pitch < -M_PI / 2)
		gui->pitch = -M_PI / 2;
}