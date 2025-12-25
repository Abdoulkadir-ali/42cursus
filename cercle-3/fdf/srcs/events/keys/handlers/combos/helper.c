/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:27:35 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:18:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	clamp_values(t_events *events)
{
	clamp_float(&events->lod_value, MIN_LOD_LEVEL, MAX_LOD_LEVEL);
	clamp_double(&events->camera->z_scale, MIN_Z_SCALE, MAX_Z_SCALE);
	clamp_double(&events->camera->alpha, 1.0, 180.0);
	clamp_uint(&events->map->z_divisor, 1, 100);
	events->camera->z_scale = floor(events->camera->z_scale * 10.0) / 10.0;
}

void	apply_plus_changes(t_events *events)
{
	t_keys	*keyboard;

	keyboard = &events->keys;
	if (keyboard->a)
		events->camera->alpha += 2.0;
	else if (keyboard->v)
		events->camera->z_scale -= 0.1;
	else if (keyboard->w)
		events->camera->rotation_speed -= DEFAULT_ROTATION_SPEED * 0.2;
	else if (keyboard->t)
		events->map->z_divisor += 1;
	clamp_values(events);
}

void	apply_minus_changes(t_events *events)
{
	t_keys	*keyboard;

	keyboard = &events->keys;
	if (keyboard->a)
		events->camera->alpha -= 2.0;
	else if (keyboard->v)
		events->camera->z_scale -= 0.1;
	else if (keyboard->w)
	{
		events->camera->rotation_speed -= DEFAULT_ROTATION_SPEED * 0.2;
		if (events->camera->rotation_speed < DEFAULT_ROTATION_SPEED * 0.1)
			events->camera->rotation_speed = DEFAULT_ROTATION_SPEED * 0.1;
	}
	else if (keyboard->t)
		events->map->z_divisor -= 1;
	clamp_values(events);
}

void	apply_zero_changes(t_events *events)
{
	(void)events;
}

int	check_if_changed(t_events *events, t_combo_ctx *ctx)
{
	if (fabs(ctx->old_z - events->camera->z_scale) > 0.0001
		|| fabs(ctx->old_rot_speed - events->camera->rotation_speed) > 0.0001
		|| fabs(ctx->old_alpha - events->camera->alpha) > 0.001
		|| ctx->old_z_divisor != events->map->z_divisor)
		return (1);
	return (0);
}
