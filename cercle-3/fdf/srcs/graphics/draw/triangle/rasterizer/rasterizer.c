/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:35:52 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:43:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Rasterize a flat-bottom triangle.
 * @param g Graphics state providing scanline drawing.
 * @param top Top vertex.
 * @param b1 First bottom vertex.
 * @param b2 Second bottom vertex.
 */
void	rasterize_flat_bottom(t_graphics *g, t_point top, t_point b1,
		t_point b2)
{
	t_rstr_ctx			ctx;
	t_rasterize_points	points;

	points = (t_rasterize_points){top, b1, b2};
	setup_rasterization_context(&ctx, points);
	handle_y_clipping(&ctx);
	rasterize_span(g, &ctx);
}

/**
 * @brief Rasterize a flat-top triangle.
 * @param g Graphics state providing scanline drawing.
 * @param t1 First top vertex.
 * @param t2 Second top vertex.
 * @param bot Bottom vertex.
 */
void	rasterize_flat_top(t_graphics *g, t_point t1, t_point t2, t_point bot)
{
	t_rstr_ctx			ctx;
	t_rasterize_points	points;

	points = (t_rasterize_points){t1, t2, bot};
	setup_rasterization_context_flat_top(&ctx, points);
	handle_y_clipping(&ctx);
	rasterize_span(g, &ctx);
}
