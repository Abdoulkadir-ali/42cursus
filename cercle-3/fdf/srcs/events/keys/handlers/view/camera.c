/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Cycle the camera projection mode.
 * @param events Event context owning the camera state.
 */
void	cycle_projection(t_events *events)
{
	events->camera->projection = (events->camera->projection + 1) % PROJ_COUNT;
}

/**
 * @brief Refit the camera to the current map.
 * @param events Event context owning the camera manager.
 */
void	reset_view(t_events *events)
{
	adjust_camera_to_map(events->camera_manager);
}

/**
 * @brief Cycle the projection mode and request a graphics refresh.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the camera and graphics state.
 * @return Always `1`.
 */
int	handle_p(int keycode, t_events *events)
{
	(void)keycode;
	cycle_projection(events);
	events->graphics->needs_refresh = 1;
	return (1);
}

/**
 * @brief Process held movement flags and update the camera offset.
 * @param events Event context owning the camera and key state.
 * @return Non-zero when movement changed.
 */
int	process_movement(t_events *events)
{
	t_movement_ctx	ctx;

	if (!events || !events->camera)
		return (0);
	init_movement_ctx(&ctx, events);
	calculate_movement_vector(&ctx, events);
	if (ctx.v.x != 0 || ctx.v.y != 0)
	{
		apply_movement(&ctx, events);
		clamp_offset(events);
		return (1);
	}
	return (0);
}
