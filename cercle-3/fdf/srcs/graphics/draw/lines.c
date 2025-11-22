/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:42:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 03:48:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "graphics.h"
#include <math.h>

/* Helper to manage memory pointers */
typedef struct s_ptr_ctx
{
	char			*img_ptr;
	float			*z_ptr;
	int				step_x;
	int				step_y;
	int				z_step_x;
	int				z_step_y;
	int				bpp;
	int				line_len;
	int				width;
	int				height;
}					t_ptr_ctx;

static void	setup_pointers(t_graphics *g, t_ptr_ctx *ctx, int sx, int sy)
{
	ctx->bpp = g->window->main_img.img_bpp / 8;
	ctx->line_len = g->window->main_img.img_line_len;
	ctx->width = g->window->width;
	ctx->height = g->window->height;
	/* Pre-calculate the memory jump size */
	ctx->step_x = sx * ctx->bpp;
	ctx->step_y = sy * ctx->line_len;
	ctx->z_step_x = sx;
	ctx->z_step_y = sy * ctx->width;
}

void draw_line(t_graphics *g, t_point start, t_point end)
{
	int x0 = (int)start.pos.x;
	int y0 = (int)start.pos.y;
	int x1 = (int)end.pos.x;
	int y1 = (int)end.pos.y;
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;

	/* Bounds check setup */
	t_ptr_ctx ctx;
	setup_pointers(g, &ctx, sx, sy);

	/* If start point is off-screen, standard clipping should handle it, 
	   but we add a safety return to prevent segfaults during pointer walking */
	if (x0 < 0 || x0 >= ctx.width || y0 < 0 || y0 >= ctx.height)
		return ;

	/* Initialize Pointers */
	char *pixel_addr = g->window->main_img.img_addr + (y0 * ctx.line_len) + (x0 * ctx.bpp);
	float *z_addr = NULL;
	if (g->window->z_buffer)
		z_addr = g->window->z_buffer + (y0 * ctx.width) + x0;

	/* Interpolation Setup (using doubles for precision, could be fixed-point) */
	int steps = (dx > dy) ? dx : dy;
	double zr = start.pos.z;
	double z_step_val = (steps > 0) ? (end.pos.z - start.pos.z) / steps : 0;
	
	/* Color Interpolation Setup */
	t_vec3 start_rgb = get_vec3(start.color);
	t_vec3 end_rgb = get_vec3(end.color);
	double r = start_rgb.x, g_val = start_rgb.y, b = start_rgb.z;
	double dr = 0, dg = 0, db = 0;
	if (steps > 0)
	{
		dr = (end_rgb.x - r) / steps;
		dg = (end_rgb.y - g_val) / steps;
		db = (end_rgb.z - b) / steps;
	}

	int color;
	int x = x0;
	int y = y0;

	while (1)
	{
		/* 1. Z-Buffer Check using pointer */
		if (!g->render_config.use_depth_culling || !z_addr || zr < *z_addr)
		{
			if (g->render_config.use_depth_culling && z_addr)
				*z_addr = (float)zr;

			/* 2. Color Composition */
			color = create_color((int)r, (int)g_val, (int)b);
			if (g->camera->color_shift.x || g->camera->color_shift.y || g->camera->color_shift.z)
				color = shift_color(color, g->camera->color_shift.x, g->camera->color_shift.y, g->camera->color_shift.z);

			/* 3. Direct Memory Write (No multiplication!) */
			*(unsigned int *)pixel_addr = color;
		}

		if (x == x1 && y == y1) break;

		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
			/* Boundary Check: Break if we leave screen */
			if (x < 0 || x >= ctx.width) break;
			
			/* Move pointers X step */
			pixel_addr += ctx.step_x;
			if (z_addr) z_addr += ctx.z_step_x;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
			/* Boundary Check */
			if (y < 0 || y >= ctx.height) break;

			/* Move pointers Y step */
			pixel_addr += ctx.step_y;
			if (z_addr) z_addr += ctx.z_step_y;
		}
		
		/* Increment Interpolators */
		zr += z_step_val;
		r += dr; g_val += dg; b += db;
	}
}