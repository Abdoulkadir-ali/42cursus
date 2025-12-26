/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:50:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

void	render_scene(t_graphics *g)
{
	if (!g || !g->map || !g->camera)
		return ;
	if (!is_map_visible(g))
	{
		clear_frame_buffers(g);
		return ;
	}
	geometry_processing(g);
	rasterization(g);
}
