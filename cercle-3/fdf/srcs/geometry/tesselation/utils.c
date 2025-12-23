/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:35:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 16:15:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vec3d	mix_pos(t_vec3d p1, t_vec3d p2, double ratio)
{
	t_vec3d	res;

	res.x = p1.x + (p2.x - p1.x) * ratio;
	res.y = p1.y + (p2.y - p1.y) * ratio;
	res.z = p1.z + (p2.z - p1.z) * ratio;
	return (res);
}

void	set_point(t_map *dst, t_vec2 dst_pos, t_vec3d pos, int color)
{
	int	idx;

	idx = dst_pos.y * dst->width + dst_pos.x;
	dst->points.raw[idx] = pos;
	dst->points.pos[idx] = pos;
	dst->points.color[idx] = color;
}

void	init_diagonal_ctx(t_tess_diagonal_ctx *ctx, t_map *src)
{
	t_vec2	color_pair1;
	t_vec2	color_pair2;

	ctx->p1 = src->points.raw[ctx->idx];
	ctx->p2 = src->points.raw[ctx->idx + src->width + 1];
	ctx->colors1.x = src->points.color[ctx->idx];
	ctx->colors1.y = src->points.color[ctx->idx + src->width + 1];
	ctx->res1 = mix_pos(ctx->p1, ctx->p2, 0.5);
	color_pair1.x = (unsigned int)ctx->colors1.x;
	color_pair1.y = (unsigned int)ctx->colors1.y;
	ctx->col_vec.x = (int)interpolate_color(color_pair1.x, color_pair1.y, 0.5);
	ctx->p3 = src->points.raw[ctx->idx + 1];
	ctx->p4 = src->points.raw[ctx->idx + src->width];
	ctx->colors2.x = src->points.color[ctx->idx + 1];
	ctx->colors2.y = src->points.color[ctx->idx + src->width];
	ctx->res2 = mix_pos(ctx->p3, ctx->p4, 0.5);
	color_pair2.x = (unsigned int)ctx->colors2.x;
	color_pair2.y = (unsigned int)ctx->colors2.y;
	ctx->col_vec.y = (int)interpolate_color(color_pair2.x, color_pair2.y, 0.5);
}
