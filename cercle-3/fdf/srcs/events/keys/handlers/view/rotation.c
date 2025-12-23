/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:02:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:45:39 by abdoali          ###   ########.fr       */
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

static void	handle_rotation_keys(t_events *events, t_vec3d *target,
						double speed)
{
	if (events->keys.x)
		target->x += speed;
	if (events->keys.y)
		target->y += speed;
	if (events->keys.z)
		target->z += speed;
}

static int	apply_rotation_lerp(t_vec3d *rot, t_vec3d *target, double factor)
{
	int	changed;

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
	return (changed);
}

int	process_rotation(t_events *events)
{
	t_vec3d	*rot;
	t_vec3d	*target;
	double	factor;
	int		changed;

	if (!events || !events->camera)
		return (0);
	rot = &events->camera->rotation;
	target = &events->camera->target_rotation;
	handle_rotation_keys(events, target, events->camera->rotation_speed);
	factor = 0.25;
	changed = apply_rotation_lerp(rot, target, factor);
	if (changed)
		update_rotation_matrix(events->camera);
	return (changed);
}
