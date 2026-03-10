/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Silence an intentionally unused keycode parameter.
 * @param keycode X11 keycode to ignore.
 */
static void	ignore_keycode(int keycode)
{
	(void)keycode;
}

/**
 * @brief Snapshot combo-controlled values before applying a change.
 * @param ctx Combo context receiving the old values.
 * @param events Event context owning the camera and map state.
 */
static void	store_old_values(t_combo_ctx *ctx, t_events *events)
{
	ctx->old_z = events->camera->z_scale;
	ctx->old_alpha = events->camera->alpha;
	ctx->old_rot_speed = events->camera->rotation_speed;
	ctx->old_z_divisor = events->map->z_divisor;
}

/**
 * @brief Apply the active plus-key combo and report whether anything changed.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the combo-controlled state.
 * @return `1` when any tracked value changed, otherwise `0`.
 */
int	handle_plus(int keycode, t_events *events)
{
	t_combo_ctx	ctx;

	ignore_keycode(keycode);
	store_old_values(&ctx, events);
	apply_plus_changes(events);
	return (check_if_changed(events, &ctx));
}

/**
 * @brief Apply the active minus-key combo and report whether anything changed.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the combo-controlled state.
 * @return `1` when any tracked value changed, otherwise `0`.
 */
int	handle_minus(int keycode, t_events *events)
{
	t_combo_ctx	ctx;

	ignore_keycode(keycode);
	store_old_values(&ctx, events);
	apply_minus_changes(events);
	return (check_if_changed(events, &ctx));
}

/**
 * @brief Apply the zero-key combo action.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the combo-controlled state.
 * @return Always `1`.
 */
int	handle_0(int keycode, t_events *events)
{
	ignore_keycode(keycode);
	apply_zero_changes(events);
	return (1);
}
