/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:35:52 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:40:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	rasterize_flat_bottom(t_graphics *g, t_point top, t_point b1,
		t_point b2)
{
	t_rasterize_ctx	ctx;

	setup_rasterization_context(&ctx, top, b1, b2);
	handle_y_clipping(&ctx);
	rasterize_span(g, &ctx);
}

void	rasterize_flat_top(t_graphics *g, t_point t1, t_point t2,
		t_point bot)
{
	t_rasterize_ctx	ctx;

	setup_rasterization_context_flat_top(&ctx, t1, t2, bot);
	handle_y_clipping(&ctx);
	rasterize_span(g, &ctx);
}
