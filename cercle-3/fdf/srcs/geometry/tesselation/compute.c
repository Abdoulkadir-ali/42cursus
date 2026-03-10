/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Compute one point in the tessellated destination grid.
 * @param src Source map providing neighboring points.
 * @param dst Destination map being filled.
 * @param pos Destination coordinates to compute.
 */
void	compute_tesselated_point(t_map *src, t_map *dst, t_vec2 pos)
{
	t_tess_compute_ctx	ctx;

	ctx.dst_pos = pos;
	ctx.src_pos.x = pos.x / 2;
	ctx.src_pos.y = pos.y / 2;
	if (pos.x % 2 == 0 && pos.y % 2 == 0)
		handle_direct_copy(src, dst, ctx.dst_pos, ctx.src_pos);
	else if (pos.x % 2 != 0 && pos.y % 2 == 0)
		handle_horizontal_interp(src, dst, ctx.dst_pos, ctx.src_pos);
	else if (pos.x % 2 == 0 && pos.y % 2 != 0)
		handle_vertical_interp(src, dst, ctx.dst_pos, ctx.src_pos);
	else
		handle_diagonal_interp(src, dst, ctx.dst_pos, ctx.src_pos);
}
