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
** Blends two colors with alpha.
*/
static unsigned int	color_blend(unsigned int dst, int src, float alpha)
{
	int	r;
	int	g;
	int	b;

	r = ((src >> 16) & 0xFF) * alpha + ((dst >> 16) & 0xFF) * (1.0 - alpha);
	g = ((src >> 8) & 0xFF) * alpha + ((dst >> 8) & 0xFF) * (1.0 - alpha);
	b = (src & 0xFF) * alpha + (dst & 0xFF) * (1.0 - alpha);
	return ((r << 16) | (g << 8) | b);
}

/*
** Draws a semi-transparent panel with a border.
*/
static void	draw_panel(t_gui *gui, int x, int y, int w, int h, int bg, int brd)
{
	int		i;
	int		j;
	char	*dst;
	int		col;
	float	a;

	j = y;
	while (j < y + h)
	{
		i = x;
		while (i < x + w)
		{
			if (i >= 0 && i < gui->win.width && j >= 0 && j < gui->win.height)
			{
				dst = gui->win.addr + (j * gui->win.line_len + i * 4);
				col = (i == x || i == x + w - 1 || j == y || j == y + h - 1)
					? brd : bg;
				a = (col == brd) ? 0.9 : 0.65;
				*(unsigned int *)dst = color_blend(*(unsigned int *)dst, col, a);
			}
			i++;
		}
		j++;
	}
}

static inline void	put_pixel_unsafe(t_gui *gui, int x, int y, int color_int)
{
	char	*dst;

	dst = gui->win.addr + (y * gui->win.line_len + x * (gui->win.bpp / 8));
	*(unsigned int *)dst = color_int;
}

/*
** Processes a single pixel (or block of pixels) by tracing a ray.
*/
static void	process_pixel(t_render_ctx *ctx, int x, int y)
{
	t_ray	ray;
	t_vec3	color;
	int		c_int;
	double	px;
	double	py;
	t_vec3	dir;
	int		dx;
	int		dy;

	px = (2.0 * (x + 0.5) / ctx->gui->win.width - 1.0) * ctx->half_width
		* ctx->aspect_ratio;
	py = (1.0 - 2.0 * (y + 0.5) / ctx->gui->win.height) * ctx->half_height
		* ctx->aspect_ratio;
	dir = vec3_norm(vec3_add(ctx->transform.forward,
				vec3_add(vec3_scale(ctx->transform.right, px),
					vec3_scale(ctx->transform.up, py))));
	ray_init(&ray, ctx->transform.pos, dir);
	color = trace_ray(ctx->gui->bvh, &ray, ctx->gui->scene);
	c_int = (((int)color.x & 0xFF) << 16) | (((int)color.y & 0xFF) << 8)
		| ((int)color.z & 0xFF);
	if (ctx->step > 1)
	{
		dy = 0;
		while (dy < ctx->step && (y + dy) < ctx->gui->win.height)
		{
			dx = 0;
			while (dx < ctx->step && (x + dx) < ctx->gui->win.width)
			{
				put_pixel_unsafe(ctx->gui, x + dx, y + dy, c_int);
				dx++;
			}
			dy++;
		}
	}
	else
		put_pixel_unsafe(ctx->gui, x, y, c_int);
}

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
		while (y < ty + TILE_SIZE && y < ctx->gui->win.height)
		{
			x = tx;
			while (x < tx + TILE_SIZE && x < ctx->gui->win.width)
			{
				process_pixel(ctx, x, y);
				x += ctx->step;
			}
			y += ctx->step;
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
** Draws UI overlays (info panels).
*/
static void	draw_ui(t_gui *gui, t_camera_controller *ctrl)
{
	char	buf[128];
	int		gold;
	int		wht;

	gold = 0xD0A000;
	wht = 0xEEEEEE;
	draw_panel(gui, 15, 15, 300, 110, 0x050505, gold);
	draw_panel(gui, 15, gui->win.height - 65, 450, 50, 0x050505, 0x444444);
	draw_panel(gui, gui->win.width - 110, 15, 95, 35, 0x050505, 0x00FF00);
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 35, gold, ">>> minRT SYSTEM v1.0");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 60, wht, "MOVE: WASD/SPACE/SHIFT");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 80, wht, "VIEW: LMB+DRAG");
	mlx_string_put(gui->win.mlx, gui->win.win, 30, 100, wht, "FOV : MMB+DRAG");
	sprintf(buf, "POS: %.2f %.2f %.2f", ctrl->transform.pos.x,
		ctrl->transform.pos.y, ctrl->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 30, gui->win.height - 52, wht, buf);
	sprintf(buf, "ROT: %.1f %.1f", ctrl->transform.rotation.pitch * 57.29,
		ctrl->transform.rotation.yaw * 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, 30, gui->win.height - 35, wht, buf);
	sprintf(buf, "%.1f FPS", gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->win.width - 100, 37, 0x00FF00, buf);
}

/*
** Handles mouse hover detection and display.
*/
static void	handle_hover(t_gui *gui, t_render_ctx *ctx)
{
	t_hit	hit;
	t_ray	ray;
	t_vec3	dir;
	double	px;
	double	py;

	px = (2.0 * (gui->input.mouse_x + 0.5) / gui->win.width - 1.0) * ctx->half_width
		* ctx->aspect_ratio;
	py = (1.0 - 2.0 * (gui->input.mouse_y + 0.5) / gui->win.height) * ctx->half_height
		* ctx->aspect_ratio;
	dir = vec3_norm(vec3_add(ctx->transform.forward,
				vec3_add(vec3_scale(ctx->transform.right, px),
					vec3_scale(ctx->transform.up, py))));
	ray_init(&ray, ctx->transform.pos, dir);
	ft_memset(&hit, 0, sizeof(t_hit));
	if (bvh_intersect(gui->bvh, &ray, &hit))
	{
		draw_panel(gui, gui->input.mouse_x + 20, gui->input.mouse_y + 20, 220, 100,
			0x050505, 0x00D0D0);
		mlx_string_put(gui->win.mlx, gui->win.win, gui->input.mouse_x + 35,
			gui->input.mouse_y + 55, 0x00D0D0, "OBJECT HIT");
	}
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
	mlx_put_image_to_window(gui->win.mlx, gui->win.win, gui->win.img, 0, 0);
	draw_ui(gui, &gui->cam_ctrl);
	handle_hover(gui, &ctx);
}
