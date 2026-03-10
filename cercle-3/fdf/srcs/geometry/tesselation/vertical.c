/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Interpolate a point between vertical neighbors.
 * @param src Source map.
 * @param dst Destination tessellated map.
 * @param dst_pos Destination coordinates.
 * @param src_pos Source coordinates at the top endpoint.
 */
void	handle_vertical_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	t_tess_vertical_ctx	ctx;
	t_set_point_ctx		set_ctx;

	ctx.idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.y + 1 >= (int)src->height)
	{
		set_ctx.dst_pos = dst_pos;
		set_ctx.pos = src->points.raw[ctx.idx];
		set_ctx.color = src->points.color[ctx.idx];
		set_ctx.source_color = src->points.source_color[ctx.idx];
		set_point(dst, set_ctx);
		return ;
	}
	ctx.p1 = src->points.raw[ctx.idx];
	ctx.p2 = src->points.raw[ctx.idx + src->width];
	ctx.col1 = src->points.color[ctx.idx];
	ctx.col2 = src->points.color[ctx.idx + src->width];
	ctx.sc1 = src->points.source_color[ctx.idx];
	ctx.sc2 = src->points.source_color[ctx.idx + src->width];
	set_ctx.dst_pos = dst_pos;
	set_ctx.pos = mix_pos(ctx.p1, ctx.p2, 0.5);
	set_ctx.color = interpolate_color(ctx.col1, ctx.col2, 0.5);
	set_ctx.source_color = interpolate_color(ctx.sc1, ctx.sc2, 0.5);
	set_point(dst, set_ctx);
}
