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

static void	draw_panel(t_gui *gui, int x, int y, int w, int h, int bg_color,
		int border_color)
{
	float			alpha;
	bool			is_border;
	char			*dst;
	unsigned int	bg;
	int				current_color;
	float			current_alpha;
	int				r;
	int				g;
	int				b;

	int i, j;
	alpha = 0.65;
	for (j = y; j < y + h; j++)
	{
		for (i = x; i < x + w; i++)
		{
			if (i < 0 || i >= gui->width || j < 0 || j >= gui->height)
				continue ;
			// Border Check
			is_border = (i == x || i == x + w - 1 || j == y || j == y + h - 1);
			dst = gui->addr + (j * gui->line_length + i * (gui->bits_per_pixel
						/ 8));
			bg = *(unsigned int *)dst;
			current_color = is_border ? border_color : bg_color;
			current_alpha = is_border ? 0.9 : alpha;
			r = ((current_color >> 16) & 0xFF) * current_alpha
				+ ((bg >> 16) & 0xFF) * (1.0 - current_alpha);
			g = ((current_color >> 8) & 0xFF) * current_alpha
				+ ((bg >> 8) & 0xFF) * (1.0 - current_alpha);
			b = (current_color & 0xFF) * current_alpha + (bg & 0xFF) * (1.0
					- current_alpha);
			*(unsigned int *)dst = (r << 16) | (g << 8) | b;
		}
	}
}

static inline void	put_pixel_unsafe(t_gui *gui, int x, int y, int color_int)
{
	char	*dst;

	dst = gui->addr + (y * gui->line_length + x * (gui->bits_per_pixel / 8));
	*(unsigned int *)dst = color_int;
}

static void	*render_tile_worker(void *arg)
{
	t_render_ctx	*ctx;
	t_ray			ray;
	t_vec3			color;
	int				color_int;
	int				tile_id;
	double			px;
	double			py;
	t_vec3			dir;

	ctx = (t_render_ctx *)arg;
	int tx, ty, x, y, dx, dy;
	while (1)
	{
		// 1. Atomic Ticket Grab
		pthread_mutex_lock(&ctx->mutex);
		if (ctx->next_tile_id >= ctx->total_tiles)
		{
			pthread_mutex_unlock(&ctx->mutex);
			break ;
		}
		tile_id = ctx->next_tile_id++;
		pthread_mutex_unlock(&ctx->mutex);
		// 2. Determine Tile Coordinates
		tx = (tile_id % ctx->tiles_x) * TILE_SIZE;
		ty = (tile_id / ctx->tiles_x) * TILE_SIZE;
		// 3. Render Tile [16x16]
		// Loop Y within tile
		for (y = ty; y < ty + TILE_SIZE && y < ctx->gui->height; y += ctx->step)
		{
			// Loop X within tile
			for (x = tx; x < tx + TILE_SIZE && x < ctx->gui->width; x
				+= ctx->step)
			{
				px = (2.0 * (x + 0.5) / ctx->gui->width - 1.0) * ctx->half_width
					* ctx->aspect_ratio;
				py = (1.0 - 2.0 * (y + 0.5) / ctx->gui->height)
					* ctx->half_height * ctx->aspect_ratio;
				dir = vec3_norm(vec3_add(ctx->forward,
							vec3_add(vec3_scale(ctx->right, px),
								vec3_scale(ctx->up, py))));
				ray_init(&ray, ctx->cam_pos, dir);
				color = trace_ray(ctx->gui->bvh, &ray, ctx->gui->scene);
				color_int = (((int)color.x & 0xFF) << 16) | (((int)color.y & 0xFF) << 8) | ((int)color.z & 0xFF);
				// Fill Block (if step > 1)
				if (ctx->step > 1)
				{
					for (dy = 0; dy < ctx->step && (y
							+ dy) < ctx->gui->height; dy++)
						for (dx = 0; dx < ctx->step && (x
								+ dx) < ctx->gui->width; dx++)
							put_pixel_unsafe(ctx->gui, x + dx, y + dy,
								color_int);
				}
				else
				{
					put_pixel_unsafe(ctx->gui, x, y, color_int);
				}
			}
		}
	}
	return (NULL);
}

void	gui_render(t_gui *gui)
{
	pthread_t		threads[THREAD_COUNT];
	t_render_ctx	ctx;
	int				i;
	double			fov_deg;
	double			fov_rad;
	int				tiles_y;
	t_hit			h;
	bool			hovering;
	double			hx;
	double			hy;
	t_vec3			hdir;
	t_ray			hray;
	int				hover_x;
	int				hover_y;
	int				txt_gold;
	int				txt_white;
	int				txt_cyan;
	char			s_pos[128], s_opt[128], s_rot[128];
	char			fps_txt[16];
	char			*type;
	t_vec3			pos;
		char h_id[64], h_pos[64];

	// 1. Setup Context
	ctx.gui = gui;
	ctx.step = gui->render_scale;
	if (ctx.step < 1)
		ctx.step = 1;
	// Camera Setup
	fov_deg = (gui->camera) ? gui->camera->fov : 70.0;
	ctx.aspect_ratio = (double)gui->width / (double)gui->height;
	fov_rad = fov_deg * M_PI / 180.0;
	ctx.half_width = tan(fov_rad / 2.0);
	ctx.half_height = ctx.half_width / ctx.aspect_ratio;
	ctx.cam_pos = (gui->camera) ? gui->camera->transform.pos : vec3(0, 0, 0);
	ctx.forward = get_camera_forward(gui->rotation.pitch, gui->rotation.yaw);
	ctx.right = vec3_norm(vec3_cross(ctx.forward, vec3(0, 1, 0)));
		// Switch to Y-up
	if (vec3_mag_sq(ctx.right) < 1e-6)
		ctx.right = vec3(1, 0, 0);
	ctx.up = vec3_cross(ctx.right, ctx.forward);
	// Sync to camera rotator object
	if (gui->camera)
	{
		gui->camera->transform.rotation = gui->rotation;
		gui->camera->transform.forward = ctx.forward;
		gui->camera->transform.right = ctx.right;
		gui->camera->transform.up = ctx.up;
	}
	// Tiling Setup
	ctx.tiles_x = (gui->width + TILE_SIZE - 1) / TILE_SIZE;
	tiles_y = (gui->height + TILE_SIZE - 1) / TILE_SIZE;
	ctx.total_tiles = ctx.tiles_x * tiles_y;
	ctx.next_tile_id = 0;
	pthread_mutex_init(&ctx.mutex, NULL);
	// 2. Validated Scaling
	// If low-res,simply rendering fewer pixels inside the tile loop handles it naturally.
	// The loops inside render_tile_worker handle ctx.step.
	// 3. Launch Threads
	for (i = 0; i < THREAD_COUNT; i++)
	{
		pthread_create(&threads[i], NULL, render_tile_worker, &ctx);
	}
	// 4. Join Threads
	for (i = 0; i < THREAD_COUNT; i++)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&ctx.mutex);

	// --- PRE-RENDERING UI LAYOUT ---
	// 1. Hover Logic (Pre-calculated to decide on popup)
	ft_memset(&h, 0, sizeof(t_hit));
	hovering = false;
	hx = (2.0 * (ctx.gui->mouse_x + 0.5) / ctx.gui->width - 1.0)
		* ctx.half_width * ctx.aspect_ratio;
	hy = (1.0 - 2.0 * (ctx.gui->mouse_y + 0.5) / ctx.gui->height)
		* ctx.half_height * ctx.aspect_ratio;
	hdir = vec3_norm(vec3_add(ctx.forward, vec3_add(vec3_scale(ctx.right, hx),
					vec3_scale(ctx.up, hy))));
	ray_init(&hray, ctx.cam_pos, hdir);
	hover_x = gui->mouse_x + 20;
	hover_y = gui->mouse_y + 20;
	if (bvh_intersect(gui->bvh, &hray, &h))
	{
		hovering = true;
		if (hover_x + 220 > gui->width)
			hover_x -= 240;
		if (hover_y + 90 > gui->height)
			hover_y -= 110;
		draw_panel(gui, hover_x, hover_y, 220, 90, 0x050505, 0x00D0D0);
	}

	// 2. Main Controls Panel
	draw_panel(gui, 15, 15, 300, 110, 0x050505, 0xD0A000); // Gold border
	// 3. Status Panel (Pos/FOV)
	draw_panel(gui, 15, gui->height - 65, 450, 50, 0x050505, 0x444444);
	// 4. FPS Badge
	draw_panel(gui, gui->width - 110, 15, 95, 35, 0x050505, 0x00FF00);

	// --- SUBMIT TO WINDOW ---
	mlx_put_image_to_window(gui->mlx, gui->win, gui->img, 0, 0);

	// --- DRAW TEXT OVERLAYS ---
	txt_gold = 0xD0A000;
	txt_white = 0xEEEEEE;
	txt_cyan = 0x00D0D0;

	// Controls Text
	mlx_string_put(gui->mlx, gui->win, 30, 35, txt_gold, ">>> minRT SYSTEM v1.0");
	mlx_string_put(gui->mlx, gui->win, 30, 60, txt_white, "MOVE  : W A S D / SPACE / SHIFT");
	mlx_string_put(gui->mlx, gui->win, 30, 80, txt_white, "VIEW  : LMB + DRAG");
	mlx_string_put(gui->mlx, gui->win, 30, 100, txt_white, "FOV   : MMB + DRAG / SCROLL");

	// Status Text
	sprintf(s_pos, "POSITION: X:%.2f Y:%.2f Z:%.2f", ctx.cam_pos.x, ctx.cam_pos.y, ctx.cam_pos.z);
	sprintf(s_rot, "ROTATION: P:%.1f Y:%.1f R:%.1f", gui->rotation.pitch * (180.0 / M_PI), gui->rotation.yaw * (180.0 / M_PI), gui->rotation.roll * (180.0 / M_PI));
	if (gui->camera)
		sprintf(s_opt, "FOV: %.1f | SPEED: %.2f", (double)gui->camera->fov, gui->move_speed);
	else
		sprintf(s_opt, "FOV: --- | SPEED: %.2f", gui->move_speed);
	
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 52, txt_white, s_pos);
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 35, txt_white, s_rot);
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 18, txt_white, s_opt);

	sprintf(fps_txt, "%.1f FPS", gui->fps);
	mlx_string_put(gui->mlx, gui->win, gui->width - 100, 37, 0x00FF00, fps_txt);

	// Hover Popup Detail
	if (hovering)
	{
		type = "Unknown";
		pos = vec3(0, 0, 0);
		if (h.obj_type == SPHERE)
		{
			type = "Sphere";
			pos = ((t_sphere *)h.obj_ptr)->transform.pos;
		}
		else if (h.obj_type == PLANE)
		{
			type = "Plane";
			pos = ((t_plane *)h.obj_ptr)->transform.pos;
		}
		else if (h.obj_type == CYLINDER)
		{
			type = "Cylinder";
			pos = ((t_cylinder *)h.obj_ptr)->transform.pos;
		}
		else if (h.obj_type == CONE)
		{
			type = "Cone";
			pos = ((t_cone *)h.obj_ptr)->transform.pos;
		}
		else if (h.obj_type == MESH)
		{
			type = "Mesh";
		}

		sprintf(h_id, "TYPE: %s", type);
		sprintf(h_pos, "POS: %.1f, %.1f, %.1f", pos.x, pos.y, pos.z);
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 35, txt_cyan, h_id);
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 55, txt_white, h_pos);
		
		char h_dist[64];
		sprintf(h_dist, "DIST: %.2f", h.t);
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 75, 0xAAAAAA, h_dist);
	}
}
	sprintf(s_pos, "POSITION: X:%.2f Y:%.2f Z:%.2f", ctx.cam_pos.x,
		ctx.cam_pos.y, ctx.cam_pos.z);
	sprintf(s_rot, "ROTATION: P:%.1f Y:%.1f R:%.1f", gui->rotation.pitch
		* (180.0 / M_PI), gui->rotation.yaw * (180.0 / M_PI), gui->rotation.roll
		* (180.0 / M_PI));
	sprintf(s_opt, "FOV: %.1f | SPEED: %.2f", (double)gui->camera->fov,
		gui->move_speed);
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 52, txt_white, s_pos);
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 35, txt_white, s_rot);
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 18, txt_white, s_opt);
	// FPS Text
	sprintf(fps_txt, "%.1f FPS", gui->fps);
	mlx_string_put(gui->mlx, gui->win, gui->width - 100, 37, 0x00FF00, fps_txt);
	// Hover Text
	if (hovering)
	{
		type = "Unknown";
		pos = vec3(0, 0, 0);
		if (h.ref.type == TYPE_SPHERE)
		{
			type = "Sphere";
			pos = gui->scene->spheres[h.ref.index].transform.pos;
		}
		else if (h.ref.type == TYPE_PLANE)
		{
			type = "Plane";
			pos = gui->scene->planes[h.ref.index].transform.pos;
		}
		else if (h.ref.type == TYPE_CYLINDER)
		{
			type = "Cylinder";
			pos = gui->scene->cylinders[h.ref.index].transform.pos;
		}
		else if (h.ref.type == TYPE_CONE)
		{
			type = "Cone";
			pos = gui->scene->cones[h.ref.index].transform.pos;
		}
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 25, txt_cyan,
			"OBJECT DETECTED");
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 45,
			txt_white, type);
		sprintf(h_id, "ENTITY ID: %d", (int)h.ref.index);
		sprintf(h_pos, "LOC: %.1f, %.1f, %.1f", pos.x, pos.y, pos.z);
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 65, 0x888888,
			h_id);
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 80, 0x888888,
			h_pos);
	}
}
