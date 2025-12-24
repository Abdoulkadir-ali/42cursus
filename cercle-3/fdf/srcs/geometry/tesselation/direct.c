/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:29:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

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
