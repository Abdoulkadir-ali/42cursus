/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:43:49 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:57:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	handle_tesselation_points(int keycode, t_graphics *g)
{
	if (keycode == KEY_BRACKET_LEFT || keycode == XK_comma)
	{
		g->render_config.target_tesselation_points -= 1000;
		if (g->render_config.target_tesselation_points < 1000)
			g->render_config.target_tesselation_points = 1000;
		g->needs_refresh = 1;
	}
	else if (keycode == KEY_BRACKET_RIGHT || keycode == XK_period)
	{
		g->render_config.target_tesselation_points += 1000;
		if (g->render_config.target_tesselation_points > 80000)
			g->render_config.target_tesselation_points = 80000;
		g->needs_refresh = 1;
	}
}
