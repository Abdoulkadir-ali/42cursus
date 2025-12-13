/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:13:09 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:27:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	draw_pixel_with_z(t_graphics *g, t_bresenham_params *p, int color)
{
	t_pixel_draw_params	pdp;

	pdp.pixel_addr = p->pixel_addr;
	pdp.z_addr = p->z_addr;
	pdp.zr = (float)p->zr;
	pdp.color = color;
	draw_pixel_fast(g, pdp);
}

static int	bresenham_step(t_bresenham_ctx *ctx, t_bresenham_params *p)
{
	ctx->e2 = 2 * ctx->err;
	if (ctx->e2 > -p->delta.y)
		if (bresenham_step_x(ctx, p))
			return (1);
	if (ctx->e2 < p->delta.x)
		if (bresenham_step_y(ctx, p))
			return (1);
	return (0);
}

void	bresenham_fixed(t_graphics *g, t_bresenham_params p)
{
	t_bresenham_ctx	ctx;
	int				color;

	init_bresenham_ctx(&ctx, &p);
	while (1)
	{
		color = get_interpolated_color(&ctx);
		draw_pixel_with_z(g, &p, color);
		if (ctx.current.x == p.end.x && ctx.current.y == p.end.y)
			break ;
		if (bresenham_step(&ctx, &p))
			break ;
		update_bresenham_colors(&ctx, &p);
	}
}
