/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:27:35 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:32:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	clamp_values(t_events *events)
{
	if (events->lod_level < MIN_LOD_LEVEL)
		events->lod_level = MIN_LOD_LEVEL;
	if (events->lod_level > MAX_LOD_LEVEL)
		events->lod_level = MAX_LOD_LEVEL;
	if (events->camera->z_scale < MIN_Z_SCALE)
		events->camera->z_scale = MIN_Z_SCALE;
	if (events->camera->z_scale > MAX_Z_SCALE)
		events->camera->z_scale = MAX_Z_SCALE;
	if (events->camera->frustum_margin < MIN_FRUSTUM_MARGIN)
		events->camera->frustum_margin = MIN_FRUSTUM_MARGIN;
	if (events->camera->frustum_margin > MAX_FRUSTUM_MARGIN)
		events->camera->frustum_margin = MAX_FRUSTUM_MARGIN;
	if (events->camera->dampening_threshold < MIN_DAMPENING_THRESHOLD)
		events->camera->dampening_threshold = MIN_DAMPENING_THRESHOLD;
	if (events->camera->dampening_threshold > MAX_DAMPENING_THRESHOLD)
		events->camera->dampening_threshold = MAX_DAMPENING_THRESHOLD;
	if (events->camera->spline_segments < MIN_SPLINE_SEGMENTS)
		events->camera->spline_segments = MIN_SPLINE_SEGMENTS;
	if (events->camera->spline_segments > MAX_SPLINE_SEGMENTS)
		events->camera->spline_segments = MAX_SPLINE_SEGMENTS;
	events->camera->z_scale = floor(events->camera->z_scale * 10.0) / 10.0;
}

void	apply_plus_changes(t_events *events)
{
	t_keys	*keyboard;

	keyboard = &events->keys;
	if (keyboard->l)
		events->lod_level++;
	else if (keyboard->z)
		events->camera->z_scale += 0.1;
	else if (keyboard->f)
		events->camera->frustum_margin += 10;
	else if (keyboard->d)
		events->camera->dampening_threshold += 5;
	else if (keyboard->t)
		events->camera->spline_segments += 2;
	clamp_values(events);
}

void	apply_minus_changes(t_events *events)
{
	t_keys	*keyboard;

	keyboard = &events->keys;
	if (keyboard->l)
		events->lod_level--;
	else if (keyboard->z)
		events->camera->z_scale -= 0.1;
	else if (keyboard->f)
		events->camera->frustum_margin -= 10;
	else if (keyboard->d)
		events->camera->dampening_threshold -= 5;
	else if (keyboard->t)
		events->camera->spline_segments -= 2;
	clamp_values(events);
}

void	apply_zero_changes(t_events *events)
{
	t_keys	*keyboard;

	keyboard = &events->keys;
	if (keyboard->l)
		events->lod_level = DEFAULT_LOD_LEVEL;
	else if (keyboard->z)
		events->camera->z_scale = DEFAULT_Z_SCALE;
	else if (keyboard->f)
		events->camera->frustum_margin = DEFAULT_FRUSTUM_MARGIN;
	else if (keyboard->d)
		events->camera->dampening_threshold = DEFAULT_DAMPENING_THRESHOLD;
	else if (keyboard->t)
		events->camera->spline_segments = DEFAULT_SPLINE_SEGMENTS;
}

int	check_if_changed(t_events *events, t_combo_ctx *ctx)
{
	if (ctx->old_lod != events->lod_level || fabs(ctx->old_z
			- events->camera->z_scale) > 0.0001
		|| ctx->old_frust != events->camera->frustum_margin
		|| ctx->old_damp != events->camera->dampening_threshold
		|| ctx->old_spline != events->camera->spline_segments)
		return (1);
	return (0);
}
