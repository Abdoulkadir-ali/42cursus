/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:32:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static void	ignore_keycode(int keycode)
{
	(void)keycode;
}

static void	store_old_values(t_combo_ctx *ctx, t_events *events)
{
	ctx->old_lod = events->lod_value;
	ctx->old_z = events->camera->z_scale;
	ctx->old_frust = events->camera->frustum_margin;
	ctx->old_damp = events->camera->dampening_threshold;
	ctx->old_spline = events->camera->spline_segments;
	ctx->old_alpha = events->camera->alpha;
}

int	handle_plus(int keycode, t_events *events)
{
	t_combo_ctx	ctx;

	ignore_keycode(keycode);
	store_old_values(&ctx, events);
	apply_plus_changes(events);
	return (check_if_changed(events, &ctx) || events->keys.b || events->keys.d);
}

int	handle_minus(int keycode, t_events *events)
{
	t_combo_ctx	ctx;

	ignore_keycode(keycode);
	store_old_values(&ctx, events);
	apply_minus_changes(events);
	return (check_if_changed(events, &ctx) || events->keys.b || events->keys.d);
}

int	handle_0(int keycode, t_events *events)
{
	ignore_keycode(keycode);
	apply_zero_changes(events);
	return (1);
}
