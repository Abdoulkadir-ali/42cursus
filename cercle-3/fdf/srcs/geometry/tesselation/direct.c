/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Copy a source vertex into the tessellated grid.
 * @param src Source map.
 * @param dst Destination tessellated map.
 * @param dst_pos Destination coordinates.
 * @param src_pos Source coordinates.
 */
void	handle_direct_copy(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	t_tess_direct_ctx	ctx;
	t_set_point_ctx		set_ctx;

	ctx.idx = src_pos.y * src->width + src_pos.x;
	set_ctx.dst_pos = dst_pos;
	set_ctx.pos = src->points.raw[ctx.idx];
	set_ctx.color = src->points.color[ctx.idx];
	set_ctx.source_color = src->points.source_color[ctx.idx];
	set_point(dst, set_ctx);
}
