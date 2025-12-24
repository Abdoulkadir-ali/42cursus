/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 21:09:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

static void	handle_direct_copy(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	int	idx;

	idx = src_pos.y * src->width + src_pos.x;
	set_point(dst, dst_pos, src->points.raw[idx], src->points.color[idx],
		src->points.source_color[idx]);
}

static void	handle_horizontal_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	int		idx;
	t_vec3d	p1;
	t_vec3d	p2;
	t_vec3	c1;
	t_vec3	c2;
	t_vec3	sc1;
	t_vec3	sc2;

	idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.x + 1 >= (int)src->width)
	{
		set_point(dst, dst_pos, src->points.raw[idx], src->points.color[idx],
			src->points.source_color[idx]);
		return ;
	}
	p1 = src->points.raw[idx];
	p2 = src->points.raw[idx + 1];
	c1 = src->points.color[idx];
	c2 = src->points.color[idx + 1];
	sc1 = src->points.source_color[idx];
	sc2 = src->points.source_color[idx + 1];
	set_point(dst, dst_pos, mix_pos(p1, p2, 0.5), interpolate_color(c1, c2,
			0.5), interpolate_color(sc1, sc2, 0.5));
}

static void	handle_diagonal_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	t_tess_diagonal_ctx	ctx;
	t_vec3d				final_pos;
	t_vec3				final_color;
	t_vec3				final_source;

	ctx.idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.x + 1 >= (int)src->width || src_pos.y + 1 >= (int)src->height)
	{
		set_point(dst, dst_pos, src->points.raw[ctx.idx],
			src->points.color[ctx.idx], src->points.source_color[ctx.idx]);
		return ;
	}
	init_diagonal_ctx(&ctx, src);
	final_pos = mix_pos(ctx.res1, ctx.res2, 0.5);
	final_color = interpolate_color(ctx.col_vec, ctx.col_vec, 0.5);
	
	/* Interpolate source color manually or extend ctx */
	/* Since ctx doesn't hold source color, we do it here for simplicity or extend struct */
	/* Extending struct is cleaner but requires finding header. Let's do it inline for now to save tool calls */
	t_vec3 sc1 = src->points.source_color[ctx.idx];
	t_vec3 sc2 = src->points.source_color[ctx.idx + src->width + 1];
	t_vec3 scol_vec1 = interpolate_color(sc1, sc2, 0.5);
	t_vec3 sc3 = src->points.source_color[ctx.idx + 1];
	t_vec3 sc4 = src->points.source_color[ctx.idx + src->width];
	t_vec3 scol_vec2 = interpolate_color(sc3, sc4, 0.5);
	final_source = interpolate_color(scol_vec1, scol_vec2, 0.5);

	set_point(dst, dst_pos, final_pos, final_color, final_source);
}

static void	handle_vertical_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	int		idx;
	t_vec3d	p1;
	t_vec3d	p2;
	t_vec3	col1;
	t_vec3	col2;
	t_vec3	sc1;
	t_vec3	sc2;

	idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.y + 1 >= (int)src->height)
	{
		set_point(dst, dst_pos, src->points.raw[idx], src->points.color[idx],
			src->points.source_color[idx]);
		return ;
	}
	p1 = src->points.raw[idx];
	p2 = src->points.raw[idx + src->width];
	col1 = src->points.color[idx];
	col2 = src->points.color[idx + src->width];
	sc1 = src->points.source_color[idx];
	sc2 = src->points.source_color[idx + src->width];
	set_point(dst, dst_pos, mix_pos(p1, p2, 0.5), interpolate_color(col1, col2,
			0.5), interpolate_color(sc1, sc2, 0.5));
}

void	compute_tesselated_point(t_map *src, t_map *dst, int x, int y)
{
	t_vec2	dst_pos;
	t_vec2	src_pos;

	dst_pos.x = x;
	dst_pos.y = y;
	src_pos.x = x / 2;
	src_pos.y = y / 2;
	if (x % 2 == 0 && y % 2 == 0)
		handle_direct_copy(src, dst, dst_pos, src_pos);
	else if (x % 2 != 0 && y % 2 == 0)
		handle_horizontal_interp(src, dst, dst_pos, src_pos);
	else if (x % 2 == 0 && y % 2 != 0)
		handle_vertical_interp(src, dst, dst_pos, src_pos);
	else
		handle_diagonal_interp(src, dst, dst_pos, src_pos);
}
