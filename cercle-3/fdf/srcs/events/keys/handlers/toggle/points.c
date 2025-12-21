/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*   Created: 2025/12/20 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "graphics.h"
#include <X11/keysym.h>
#include <stdio.h> // Debug

int	handle_manual_mode(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->graphics) return (0);
	events->graphics->render_config.use_adaptive_logic = !events->graphics->render_config.use_adaptive_logic;
	// Reset to safe defaults when switching to Manual?
	if (!events->graphics->render_config.use_adaptive_logic)
	{
		events->graphics->render_config.tesselation_level = 1;
		events->graphics->render_config.lod_value = 1.0f;
		events->graphics->render_config.use_tesselation = 1;
	}
	return (1);
}

void	handle_tesselation_points(int keycode, t_graphics *g)
{
	// Support [ ] and , . (< >)
	if (keycode == KEY_BRACKET_LEFT || keycode == XK_comma)
	{
		g->render_config.target_tesselation_points -= 1000;
		if (g->render_config.target_tesselation_points < 1000)
			g->render_config.target_tesselation_points = 1000;
		g->dirty = 1;
	}
	else if (keycode == KEY_BRACKET_RIGHT || keycode == XK_period)
	{
		g->render_config.target_tesselation_points += 1000;
		if (g->render_config.target_tesselation_points > 80000)
			g->render_config.target_tesselation_points = 80000;
		g->dirty = 1;
	}
}
