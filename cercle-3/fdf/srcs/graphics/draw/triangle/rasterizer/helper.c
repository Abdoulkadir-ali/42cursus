/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:38:46 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:39:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	setup_rasterization_context(t_rasterize_ctx *ctx, t_point p1,
		t_point p2, t_point p3)
{
	ctx->y_start = (int)p1.pos.y;
	ctx->y_end = (int)p2.pos.y;
	setup_edge(&ctx->e1, p1, p2);
	setup_edge(&ctx->e2, p1, p3);
}

void	setup_rasterization_context_flat_top(t_rasterize_ctx *ctx,
		t_point p1, t_point p2, t_point p3)
{
	ctx->y_start = (int)p1.pos.y;
	ctx->y_end = (int)p3.pos.y;
	setup_edge(&ctx->e1, p1, p3);
	setup_edge(&ctx->e2, p2, p3);
}

void	handle_y_clipping(t_rasterize_ctx *ctx)
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

t_scanline_data	create_scanline_from_edges(t_rasterize_ctx *ctx, int y)
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

void	rasterize_span(t_graphics *g, t_rasterize_ctx *ctx)
{
	t_scanline_data	data;
	int				y;

	y = ctx->y_start;
	while (y < ctx->y_end)
	{
		if (y >= g->window->height)
			break ;
		data = create_scanline_from_edges(ctx, y);
		draw_horizontal_scanline_z(g, data);
		step_edge(&ctx->e1);
		step_edge(&ctx->e2);
		y++;
	}
}
