/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "gui.h"

static int	pack_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = ((int)color.x & 0xFF) << 16;
	g = ((int)color.y & 0xFF) << 8;
	b = (int)color.z & 0xFF;
	return (r | g | b);
}

static void	fill_block(t_render_ctx *ctx, t_fill_args *params)
{
	int		dx;
	int		dy;
	char	*dst;

	dy = 0;
	while (dy < ctx->step && (params->y + dy) < ctx->gui->win.height)
	{
		dst = params->pixel_addr + (dy * ctx->gui->win.line_len);
		dx = 0;
		while (dx < ctx->step && (params->x + dx) < ctx->gui->win.width)
		{
			*(unsigned int *)(dst + (dx * 4)) = params->color;
			dx++;
		}
		dy++;
	}
}

void	process_pixel(t_render_ctx *ctx, t_vec2i pos, char *pixel_addr)
{
	t_ray			ray;
	t_vec3			color;
	int				c_int;
	t_fill_args	params;

	make_camera_ray(ctx, pos.x, pos.y, &ray);
	color = trace_ray(&ctx->gui->rt, &ray);
	c_int = pack_color(color);
	if (ctx->step > 1)
	{
		params.x = pos.x;
		params.y = pos.y;
		params.color = c_int;
		params.pixel_addr = pixel_addr;
		fill_block(ctx, &params);
	}
	else
		*(unsigned int *)pixel_addr = c_int;
}
