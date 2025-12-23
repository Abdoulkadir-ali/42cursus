/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:46:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:51:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_standard_segment(t_segment_ctx *ctx, t_graphics *g,
		t_draw_line_params params)
{
	t_point	p2;

	p2 = get_cached_proj(g, ctx->next_x, ctx->next_y);
	if (!should_draw_line(params.p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, params.p1, p2);
}

void	draw_segment(t_graphics *g, t_draw_line_params params,
		int is_horizontal)
{
	t_segment_ctx	ctx;

	compute_next_coords(&ctx, params, is_horizontal);
	if (ctx.next_x >= g->map->width || ctx.next_y >= g->map->height)
		return ;
	if (g->render_config.render_mode == RENDER_LINES
		&& g->render_config.lod_value < 1.0)
		draw_tessellated_segment(&ctx, g, params);
	draw_standard_segment(&ctx, g, params);
}
