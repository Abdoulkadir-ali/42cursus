/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:38:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:41:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Initialize edge walkers for a flat-bottom triangle.
 * @param ctx Rasterization context to populate.
 * @param points Triangle points in flat-bottom order.
 */
void	setup_rasterization_context(
		t_rstr_ctx *ctx, t_rasterize_points points)
{
	ctx->y_start = (int)points.p1.pos.y;
	ctx->y_end = (int)points.p2.pos.y;
	setup_edge(&ctx->e1, points.p1, points.p2);
	setup_edge(&ctx->e2, points.p1, points.p3);
}

/**
 * @brief Initialize edge walkers for a flat-top triangle.
 * @param ctx Rasterization context to populate.
 * @param points Triangle points in flat-top order.
 */
void	setup_rasterization_context_flat_top(
		t_rstr_ctx *ctx, t_rasterize_points points)
{
	ctx->y_start = (int)points.p1.pos.y;
	ctx->y_end = (int)points.p3.pos.y;
	setup_edge(&ctx->e1, points.p1, points.p3);
	setup_edge(&ctx->e2, points.p2, points.p3);
}

/**
 * @brief Advance edges when the triangle starts above the screen.
 * @param ctx Rasterization context to clip in place.
 */
void	handle_y_clipping(t_rstr_ctx *ctx)
{
	int	skip;
	int	k;

	if (ctx->y_start < 0)
	{
		skip = -ctx->y_start;
		k = 0;
		while (k < skip)
		{
			step_edge(&ctx->e1);
			step_edge(&ctx->e2);
			k++;
		}
		ctx->y_start = 0;
	}
}

/**
 * @brief Build one scanline payload from the two active edges.
 * @param ctx Rasterization context holding the current edges.
 * @param y Scanline y coordinate.
 * @return Scanline data for the current row.
 */
t_scanline_data	create_scanline_from_edges(t_rstr_ctx *ctx, int y)
{
	t_scanline_data	data;

	data.y = y;
	data.x1 = (int)ctx->e1.x;
	data.x2 = (int)ctx->e2.x;
	data.z1 = (float)ctx->e1.z;
	data.z2 = (float)ctx->e2.z;
	data.c1 = create_color((int)ctx->e1.r, (int)ctx->e1.g, (int)ctx->e1.b);
	data.c2 = create_color((int)ctx->e2.r, (int)ctx->e2.g, (int)ctx->e2.b);
	return (data);
}

/**
 * @brief Emit all scanlines between the current y bounds of a triangle half.
 * @param g Graphics state providing image dimensions.
 * @param ctx Rasterization context holding the active edges.
 */
void	rasterize_span(t_graphics *g, t_rstr_ctx *ctx)
{
	t_scanline_data	data;
	int				y;

	y = ctx->y_start;
	while (y < ctx->y_end)
	{
		if (y >= (int)g->window->height)
			break ;
		data = create_scanline_from_edges(ctx, y);
		draw_horizontal_scanline_z(g, data);
		step_edge(&ctx->e1);
		step_edge(&ctx->e2);
		y++;
	}
}
