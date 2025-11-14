/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/14 15:16:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "graphics.h"

void	redraw(t_events *events)
{
	t_graphics *g = events->graphics;
	unsigned int before = 0;
	unsigned int after = 0;
	int cx;
	int cy;
	int offset;

	g->render_config.render_mode = events->render_mode;
	g->render_config.lod_level = events->lod_level;
	g->render_config.use_depth_culling = events->use_depth_culling;
	g->render_config.fill_triangles = events->fill_triangles;
	/* sample center pixel before drawing */
	if (g->window->main_img.img_addr)
	{
		cx = g->window->width / 2;
		cy = g->window->height / 2;
		offset = cy * g->window->main_img.img_line_len + cx * (g->window->main_img.img_bpp / 8);
		before = *(unsigned int *)(g->window->main_img.img_addr + offset);
	}
	printf("[diag] redraw: map %dx%d, win %dx%d, before=0x%08x\n",
		g->map ? g->map->width : 0,
		g->map ? g->map->height : 0,
		g->window->width, g->window->height, before);

	clear_image(g);
	// clear_z_buffer(g);
	draw_grid(g);

	/* sample center pixel after drawing */
	if (g->window->main_img.img_addr)
	{
		cx = g->window->width / 2;
		cy = g->window->height / 2;
		offset = cy * g->window->main_img.img_line_len + cx * (g->window->main_img.img_bpp / 8);
		after = *(unsigned int *)(g->window->main_img.img_addr + offset);
	}
	printf("[diag] redraw: after=0x%08x\n", after);
	/* dump small block around center to verify writes */
	if (g->window->main_img.img_addr)
	{
		unsigned char *addr = (unsigned char *)g->window->main_img.img_addr;
		int bpp = g->window->main_img.img_bpp / 8;
		int line = g->window->main_img.img_line_len;
		int sx = cx - 2;
		int sy = cy - 2;
		int x, y;
		printf("[diag] image ptr=%p img=%p bpp=%d line=%d center=(%d,%d)\n",
			(void *)addr, (void *)g->window->main_img.img, bpp, line, cx, cy);
		for (y = 0; y < 5; ++y)
		{
			for (x = 0; x < 5; ++x)
			{
				int px = sx + x;
				int py = sy + y;
				if (px < 0 || py < 0 || px >= g->window->width || py >= g->window->height)
					printf("  [out] ");
				else
				{
					int off = py * line + px * bpp;
					unsigned int val = *(unsigned int *)(addr + off);
					printf(" 0x%08x", val);
				}
			}
			printf("\n");
		}
	}

	printf("[diag] calling mlx_put_image_to_window main_img=%p gui_img=%p\n",
		(void *)g->window->main_img.img, (void *)g->window->gui_img.img);
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->main_img.img, 0, 0);
	mlx_put_image_to_window(g->window->mlx_ptr, g->window->ptr,
		g->window->gui_img.img, 0, 0);
	printf("[diag] after mlx_put_image_to_window\n");
	render_gui(events->gui);
}