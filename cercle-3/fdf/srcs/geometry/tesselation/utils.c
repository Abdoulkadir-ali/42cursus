/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:35:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:26:02 by abdoali          ###   ########.fr       */
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

void	set_point(t_map *dst, t_set_point_ctx ctx)
{
	int	idx;

	idx = ctx.dst_pos.y * dst->width + ctx.dst_pos.x;
	dst->points.raw[idx] = ctx.pos;
	dst->points.pos[idx] = ctx.pos;
	dst->points.color[idx] = ctx.color;
	dst->points.source_color[idx] = ctx.source_color;
}

void	init_diagonal_ctx(t_tess_diagonal_ctx *ctx, t_map *src)
{
	ctx->p1 = src->points.raw[ctx->idx];
	ctx->p2 = src->points.raw[ctx->idx + src->width + 1];
	ctx->colors1 = src->points.color[ctx->idx];
	ctx->colors2 = src->points.color[ctx->idx + src->width + 1];
	ctx->res1 = mix_pos(ctx->p1, ctx->p2, 0.5);
	ctx->col_vec = interpolate_color(ctx->colors1, ctx->colors2, 0.5);
	ctx->col_vec1 = ctx->col_vec;
	ctx->p3 = src->points.raw[ctx->idx + 1];
	ctx->p4 = src->points.raw[ctx->idx + src->width];
	ctx->colors1 = src->points.color[ctx->idx + 1];
	ctx->colors2 = src->points.color[ctx->idx + src->width];
	ctx->res2 = mix_pos(ctx->p3, ctx->p4, 0.5);
	ctx->col_vec = interpolate_color(ctx->colors1, ctx->colors2, 0.5);
	ctx->col_vec2 = ctx->col_vec;
	ctx->sc1 = src->points.source_color[ctx->idx];
	ctx->sc2 = src->points.source_color[ctx->idx + src->width + 1];
	ctx->scol_vec1 = interpolate_color(ctx->sc1, ctx->sc2, 0.5);
	ctx->sc3 = src->points.source_color[ctx->idx + 1];
	ctx->sc4 = src->points.source_color[ctx->idx + src->width];
	ctx->scol_vec2 = interpolate_color(ctx->sc3, ctx->sc4, 0.5);
	ctx->final_source = interpolate_color(ctx->scol_vec1, ctx->scol_vec2, 0.5);
}
