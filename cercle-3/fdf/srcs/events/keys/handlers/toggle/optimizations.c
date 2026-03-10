/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:43:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Toggle adaptive logic and restore manual defaults when disabled.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return `1` when the toggle is applied, otherwise `0`.
 */
int	handle_manual_mode(int keycode, t_events *events)
{
	int	use_adaptive;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	use_adaptive = !events->graphics->render_config.use_adaptive_logic;
	events->graphics->render_config.use_adaptive_logic = use_adaptive;
	if (!events->graphics->render_config.use_adaptive_logic)
	{
		events->graphics->render_config.tesselation_level = 1;
		events->graphics->render_config.lod_value = 1.0f;
		events->graphics->render_config.use_tesselation = 1;
	}
	return (1);
}
