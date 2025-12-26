/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:33:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 19:54:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	transform_scanline(t_graphics *g, t_point *out,
		size_t row_idx, size_t width)
{
	size_t	i;
	size_t	idx;
	t_point	p;

	i = 0;
	while (i < width)
	{
		idx = row_idx + i;
		if (g->map->points.pos[idx].z > BAD_VALUE + 1.0)
		{
			p.pos = g->map->points.pos[idx];
			p.color = g->map->points.color[idx];
			out[idx] = apply_transform(p, g->camera);
		}
		else
			out[idx].pos = create_vec3d(BAD_VALUE, BAD_VALUE, BAD_VALUE);
		i++;
	}
}
