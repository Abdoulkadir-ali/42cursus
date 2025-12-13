/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_z_shifted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:13:09 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:28:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	draw_pixel_no_z(t_bresenham_params *p, int color)
{
	t_pixel_draw_params	pdp;

	pdp.pixel_addr = p->pixel_addr;
	pdp.color = color;
	draw_pixel_fast_no_z(pdp);
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

void	bresenham_fixed_no_z_shifted(t_graphics *g, t_bresenham_params p)
{
	t_bresenham_ctx	ctx;
	int				color;

	init_bresenham_ctx(&ctx, &p);
	while (1)
	{
		color = get_interpolated_color(&ctx);
		color = shift_color(color, g->camera->color_shift.x,
				g->camera->color_shift.y, g->camera->color_shift.z);
		draw_pixel_no_z(&p, color);
		if (ctx.current.x == p.end.x && ctx.current.y == p.end.y)
			break ;
		if (bresenham_step(&ctx, &p))
			break ;
		update_bresenham_colors(&ctx, &p);
	}
}
