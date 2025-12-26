/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:16:55 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:33:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_grid(t_graphics *g)
{
	if (g->render_config.use_horizon_culling)
		draw_grid_raycast_threaded(g);
	else
		draw_grid_threaded(g);
}

void	draw_grid_section(t_graphics *g, int start_y, int end_y,
		float lod_value)
{
	int	y;
	int	step_int;

	step_int = (int)lod_value;
	if (step_int < 1)
		step_int = 1;
	y = start_y;
	while (y < end_y)
	{
		draw_grid_row(g, y, lod_value);
		y += step_int;
	}
}
