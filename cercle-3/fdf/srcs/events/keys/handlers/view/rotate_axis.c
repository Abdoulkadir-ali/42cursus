/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_axis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:54:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/22 11:54:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_rot_x(int keycode, t_events *events)
{
	double	speed;

	(void)keycode;
	if (!events || !events->camera)
		return (0);
	speed = events->camera->rotation_speed;
	events->camera->target_rotation.x += speed;
	return (1);
}

int	handle_rot_y(int keycode, t_events *events)
{
	double	speed;

	(void)keycode;
	if (!events || !events->camera)
		return (0);
	speed = events->camera->rotation_speed;
	events->camera->target_rotation.y += speed;
	return (1);
}

int	handle_rot_z(int keycode, t_events *events)
{
	double	speed;

	(void)keycode;
	if (!events || !events->camera)
		return (0);
	speed = events->camera->rotation_speed;
	events->camera->target_rotation.z += speed;
	return (1);
}

int	handle_w(int keycode, t_events *events)
{
	(void)keycode;
	(void)events;
	return (1);
}
