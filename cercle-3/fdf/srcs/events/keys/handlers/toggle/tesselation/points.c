/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:43:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Adjust the target tessellation point budget within safe bounds.
 * @param keycode X11 keycode selecting the direction.
 * @param g Graphics state owning the render configuration.
 */
void	handle_tesselation_points(int keycode, t_graphics *g)
{
	if (keycode == XK_bracketleft || keycode == XK_comma)
	{
		g->render_config.target_tesselation_points -= 1000;
		if (g->render_config.target_tesselation_points < 1000)
			g->render_config.target_tesselation_points = 1000;
		g->needs_refresh = 1;
	}
	else if (keycode == XK_bracketright || keycode == XK_period)
	{
		g->render_config.target_tesselation_points += 1000;
		if (g->render_config.target_tesselation_points > 80000)
			g->render_config.target_tesselation_points = 80000;
		g->needs_refresh = 1;
	}
}
