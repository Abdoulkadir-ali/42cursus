/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Draws a semi-transparent panel with a border.
*/
/*
** Thread worker function to render tiles.
*/
static void	*render_tile_worker(void *arg)
{
	t_render_ctx	*ctx;
	int				id;
	int				tx;
	int				ty;
	int				y;
	int				x;
	char			*row_ptr;
	char			*pixel_ptr;
	int				bpp_step;
	int				row_step;

	ctx = (t_render_ctx *)arg;
	while (1)
	{
		pthread_mutex_lock(&ctx->mutex);
		if (ctx->next_tile_id >= ctx->total_tiles)
		{
			pthread_mutex_unlock(&ctx->mutex);
			break ;
		}
		id = ctx->next_tile_id++;
		pthread_mutex_unlock(&ctx->mutex);
		tx = (id % ctx->tiles_x) * TILE_SIZE;
		ty = (id / ctx->tiles_x) * TILE_SIZE;
		y = ty;
		row_ptr = ctx->gui->win.addr + (y * ctx->gui->win.line_len) + (tx * (ctx->gui->win.bpp / 8));
		bpp_step = (ctx->gui->win.bpp / 8) * ctx->step;
		row_step = ctx->gui->win.line_len * ctx->step;
		while (y < ty + TILE_SIZE && y < ctx->gui->win.height)
		{
			x = tx;
			pixel_ptr = row_ptr;
			while (x < tx + TILE_SIZE && x < ctx->gui->win.width)
			{
				process_pixel(ctx, x, y, pixel_ptr);
				x += ctx->step;
				pixel_ptr += bpp_step;
			}
			y += ctx->step;
			row_ptr += row_step;
		}
	}
	return (NULL);
}

/*
** Sets up the rendering context.
*/
static void	setup_ctx(t_gui *gui, t_render_ctx *ctx)
{
	double	fov_rad;

	ctx->gui = gui;
	ctx->step = (gui->render.scale < 1) ? 1 : gui->render.scale;
	fov_rad = (gui->cam_ctrl.camera ? gui->cam_ctrl.camera->fov : 70.0)
		* M_PI / 180.0;
	ctx->aspect_ratio = (double)gui->win.width / (double)gui->win.height;
	ctx->half_width = tan(fov_rad / 2.0);
	ctx->half_height = ctx->half_width / ctx->aspect_ratio;
	if (gui->cam_ctrl.camera)
	{
		ctx->transform = gui->cam_ctrl.camera->transform;
		ctx->transform.forward = get_camera_forward(
				gui->cam_ctrl.transform.rotation.pitch,
				gui->cam_ctrl.transform.rotation.yaw);
		ctx->transform.right = vec3_norm(vec3_cross(ctx->transform.forward,
					vec3(0, 1, 0)));
		if (vec3_mag_sq(ctx->transform.right) < 1e-6)
			ctx->transform.right = vec3(1, 0, 0);
		ctx->transform.up = vec3_cross(ctx->transform.right,
				ctx->transform.forward);
		gui->cam_ctrl.camera->transform = ctx->transform;
	}
	else
		ctx->transform = (t_transform){0};
}

/*
** Main render function.
*/
void	gui_render(t_gui *gui)
{
	t_render_ctx	ctx;
	pthread_t		threads[THREAD_COUNT];
	int				i;

	setup_ctx(gui, &ctx);
	ctx.tiles_x = (gui->win.width + TILE_SIZE - 1) / TILE_SIZE;
	ctx.total_tiles = ctx.tiles_x * ((gui->win.height + TILE_SIZE - 1) / TILE_SIZE);
	ctx.next_tile_id = 0;
	pthread_mutex_init(&ctx.mutex, NULL);
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_create(&threads[i], NULL, render_tile_worker, &ctx);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&ctx.mutex);
	draw_ui_panels(gui);
	update_hover(gui, &ctx);
	mlx_put_image_to_window(gui->win.mlx, gui->win.win, gui->win.img, 0, 0);
	draw_ui_text(gui, &gui->cam_ctrl);
	draw_hover_text(gui);
}
