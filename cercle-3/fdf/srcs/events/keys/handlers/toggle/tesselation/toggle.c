/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Toggle tessellation usage.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return `1` when the toggle is applied, otherwise `0`.
 */
int	handle_t(int keycode, t_events *events)
{
	int	use_tesselation;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	use_tesselation = !events->graphics->render_config.use_tesselation;
	events->graphics->render_config.use_tesselation = use_tesselation;
	return (1);
}

/**
 * @brief Toggle horizon culling.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return `1` when the toggle is applied, otherwise `0`.
 */
int	handle_j(int keycode, t_events *events)
{
	int	use_horizon_culling;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	use_horizon_culling = !events->graphics->render_config.use_horizon_culling;
	events->graphics->render_config.use_horizon_culling = use_horizon_culling;
	return (1);
}
