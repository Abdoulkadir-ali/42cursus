/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:16:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Dispatch grid drawing to the standard or horizon-aware path.
 * @param g Graphics state providing render configuration.
 */
void	draw_grid(t_graphics *g)
{
	if (g->render_config.use_horizon_culling)
		draw_grid_raycast_threaded(g);
	else
		draw_grid_threaded(g);
}

/**
 * @brief Draw one row band of the grid using the active LOD step.
 * @param g Graphics state providing map and render configuration.
 * @param start_y First row in the band.
 * @param end_y One-past-last row in the band.
 * @param lod_value Active LOD step value.
 */
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
