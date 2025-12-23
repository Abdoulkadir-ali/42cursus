/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 17:51:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

void	render_scene(t_graphics *g)
{
	if (!g || !g->map || !g->camera)
		return ;
	if (!g->dirty)
		return ;
	if (!is_map_visible(g))
	{
		clear_frame_buffers(g);
		g->dirty = 0;
		return ;
	}
	geometry_processing(g);
	rasterization(g);
	g->dirty = 0;
}
