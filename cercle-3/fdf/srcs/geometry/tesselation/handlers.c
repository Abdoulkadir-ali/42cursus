/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 15:48:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

static void	handle_direct_copy(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	int	idx;

	idx = src_pos.y * src->width + src_pos.x;
	set_point(dst, dst_pos, src->points.raw[idx], src->points.color[idx]);
}

static void	handle_horizontal_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	int		idx;
	t_vec3d	p1;
	t_vec3d	p2;
	t_vec2	colors;

	idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.x + 1 >= (int)src->width)
	{
		set_point(dst, dst_pos, src->points.raw[idx], src->points.color[idx]);
		return ;
	}
	p1 = src->points.raw[idx];
	p2 = src->points.raw[idx + 1];
	colors.x = src->points.color[idx];
	colors.y = src->points.color[idx + 1];
	set_point(dst, dst_pos, mix_pos(p1, p2, 0.5),
		interpolate_color((unsigned int)colors.x, (unsigned int)colors.y, 0.5));
}

static void	handle_diagonal_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	t_tess_diagonal_ctx	ctx;
	t_vec2				final_color_vec;
	t_vec3d				final_pos;
	int					final_color;

	ctx.idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.x + 1 >= (int)src->width || src_pos.y + 1 >= (int)src->height)
	{
		set_point(dst, dst_pos, src->points.raw[ctx.idx],
			src->points.color[ctx.idx]);
		return ;
	}
	init_diagonal_ctx(&ctx, src);
	final_pos = mix_pos(ctx.res1, ctx.res2, 0.5);
	final_color_vec.x = (unsigned int)ctx.col_vec.x;
	final_color_vec.y = (unsigned int)ctx.col_vec.y;
	final_color = interpolate_color(final_color_vec.x, final_color_vec.y, 0.5);
	set_point(dst, dst_pos, final_pos, final_color);
}

static void	handle_vertical_interp(t_map *src, t_map *dst, t_vec2 dst_pos,
		t_vec2 src_pos)
{
	int		idx;
	t_vec3d	p1;
	t_vec3d	p2;
	int		col1;
	int		col2;

	idx = src_pos.y * src->width + src_pos.x;
	if (src_pos.y + 1 >= (int)src->height)
	{
		set_point(dst, dst_pos, src->points.raw[idx], src->points.color[idx]);
		return ;
	}
	p1 = src->points.raw[idx];
	p2 = src->points.raw[idx + src->width];
	col1 = src->points.color[idx];
	col2 = src->points.color[idx + src->width];
	set_point(dst, dst_pos, mix_pos(p1, p2, 0.5),
		interpolate_color((unsigned int)col1, (unsigned int)col2, 0.5));
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
