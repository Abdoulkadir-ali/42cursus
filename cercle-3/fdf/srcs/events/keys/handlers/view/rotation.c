/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:02:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/22 12:02:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static double	lerp_angle(double current, double target, double factor)
{
	double	delta;

	delta = target - current;
	while (delta > M_PI)
		delta -= 2.0 * M_PI;
	while (delta < -M_PI)
		delta += 2.0 * M_PI;
	return (current + delta * factor);
}

int	process_rotation(t_events *events)
{
	t_vec3d	*rot;
	t_vec3d	*target;
	double	factor;
	double	speed;
	int		changed;

	if (!events || !events->camera)
		return (0);
	rot = &events->camera->rotation;
	target = &events->camera->target_rotation;
	speed = events->camera->rotation_speed;
	if (events->keys.x)
		target->x += speed;
	if (events->keys.y)
		target->y += speed;
	if (events->keys.z)
		target->z += speed;
	factor = 0.25;
	changed = 0;
	if (fabs(rot->x - target->x) > 0.001)
	{
		rot->x = lerp_angle(rot->x, target->x, factor);
		changed = 1;
	}
	if (fabs(rot->y - target->y) > 0.001)
	{
		rot->y = lerp_angle(rot->y, target->y, factor);
		changed = 1;
	}
	if (fabs(rot->z - target->z) > 0.001)
	{
		rot->z = lerp_angle(rot->z, target->z, factor);
		changed = 1;
	}
	if (changed)
		update_rotation_matrix(events->camera);
	return (changed);
}
