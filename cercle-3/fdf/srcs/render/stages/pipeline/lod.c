/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 17:50:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	apply_lod(t_graphics *g, int level)
{
	int	step;

	step = 1 << abs(level);
	g->render_config.lod_value = (float)step;
	g->map = g->base_map;
	if (g->tesselated_map)
	{
		free_map(g->tesselated_map);
		g->tesselated_map = NULL;
	}
}
