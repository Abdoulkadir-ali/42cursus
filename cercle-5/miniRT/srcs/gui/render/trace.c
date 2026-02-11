/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#    +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	process_pixel(t_render_ctx *ctx, int x, int y, char *pixel_addr)
{
	t_ray	ray;
	t_vec3	color;
	int		c_int;
	int		dx;
	int		dy;
	char	*dst;

	make_camera_ray(ctx, x, y, &ray);
	color = trace_ray(ctx->gui->bvh, &ray, ctx->gui->scene);
	c_int = (((int)color.x & 0xFF) << 16) | (((int)color.y & 0xFF) << 8)
		| ((int)color.z & 0xFF);
	if (ctx->step > 1)
	{
		dy = 0;
		while (dy < ctx->step && (y + dy) < ctx->gui->win.height)
		{
			dst = pixel_addr + (dy * ctx->gui->win.line_len);
			dx = 0;
			while (dx < ctx->step && (x + dx) < ctx->gui->win.width)
			{
				*(unsigned int *)(dst + (dx * 4)) = c_int;
				dx++;
			}
			dy++;
		}
	}
	else
		*(unsigned int *)pixel_addr = c_int;
}
