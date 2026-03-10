/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diagonal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Interpolate a center point from the four surrounding corners.
 * @param src Source map.
 * @param dst Destination tessellated map.
 * @param dst_pos Destination coordinates.
 * @param src_pos Source coordinates at the top-left corner.
 */
void	handle_diagonal_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	t_tess_diagonal_ctx	ctx;
	t_vec3d				final_pos;
	t_vec3				final_color;
	t_set_point_ctx		set_ctx;

	ctx.idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.x + 1 >= (int)src->width || src_pos.y + 1 >= (int)src->height)
	{
		set_ctx.dst_pos = dst_pos;
		set_ctx.pos = src->points.raw[ctx.idx];
		set_ctx.color = src->points.color[ctx.idx];
		set_ctx.source_color = src->points.source_color[ctx.idx];
		set_point(dst, set_ctx);
		return ;
	}
	init_diagonal_ctx(&ctx, src);
	final_pos = mix_pos(ctx.res1, ctx.res2, 0.5);
	final_color = interpolate_color(ctx.col_vec1, ctx.col_vec2, 0.5);
	set_ctx.dst_pos = dst_pos;
	set_ctx.pos = final_pos;
	set_ctx.color = final_color;
	set_ctx.source_color = ctx.final_source;
	set_point(dst, set_ctx);
}
