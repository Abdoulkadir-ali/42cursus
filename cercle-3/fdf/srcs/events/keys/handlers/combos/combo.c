/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:12:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static void	ignore_keycode(int keycode)
{
	(void)keycode;
}

static void	store_old_values(t_combo_ctx *ctx, t_events *events)
{
	ctx->old_z = events->camera->z_scale;
	ctx->old_alpha = events->camera->alpha;
	ctx->old_rot_speed = events->camera->rotation_speed;
	ctx->old_z_divisor = events->map->z_divisor;
}

int	handle_plus(int keycode, t_events *events)
{
	t_combo_ctx	ctx;

	ignore_keycode(keycode);
	store_old_values(&ctx, events);
	apply_plus_changes(events);
	return (check_if_changed(events, &ctx));
}

int	handle_minus(int keycode, t_events *events)
{
	t_combo_ctx	ctx;

	ignore_keycode(keycode);
	store_old_values(&ctx, events);
	apply_minus_changes(events);
	return (check_if_changed(events, &ctx));
}

int	handle_0(int keycode, t_events *events)
{
	ignore_keycode(keycode);
	apply_zero_changes(events);
	return (1);
}
