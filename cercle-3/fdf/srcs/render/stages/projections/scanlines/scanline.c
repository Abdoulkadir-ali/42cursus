/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:33:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:49:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	transform_scanline(t_graphics *g, t_point *out,
		size_t row_idx, size_t width)
{
	size_t		i;
	t_point		p;
	size_t		idx;

	i = 0;
	while (i < width)
	{
		idx = row_idx + i;
		p.pos = g->map->points.pos[idx];
		p.color = g->map->points.color[idx];
		out[idx] = apply_transform(p, g->camera);
		i++;
	}
}
