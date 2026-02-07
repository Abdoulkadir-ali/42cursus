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

static void	put_pixel(t_gui *gui, int x, int y, t_vec3 color)
{
	char	*dst;
	int		r = (int)color.x;
	int		g = (int)color.y;
	int		b = (int)color.z;

	if (x < 0 || x >= gui->width || y < 0 || y >= gui->height)
		return ;
	dst = gui->addr + (y * gui->line_length + x * (gui->bits_per_pixel / 8));
	*(unsigned int *)dst = (r << 16) | (g << 8) | b;
}

static void	draw_panel(t_gui *gui, int x, int y, int w, int h, int bg_color, int border_color)
{
	int i, j;
	float alpha = 0.65;
	
	for (j = y; j < y + h; j++)
	{
		for (i = x; i < x + w; i++)
		{
			if (i < 0 || i >= gui->width || j < 0 || j >= gui->height)
				continue;
			
			// Border Check
			bool is_border = (i == x || i == x + w - 1 || j == y || j == y + h - 1);
			
			char *dst = gui->addr + (j * gui->line_length + i * (gui->bits_per_pixel / 8));
			unsigned int bg = *(unsigned int *)dst;
			
			int current_color = is_border ? border_color : bg_color;
			float current_alpha = is_border ? 0.9 : alpha;

			int r = ((current_color >> 16) & 0xFF) * current_alpha + ((bg >> 16) & 0xFF) * (1.0 - current_alpha);
			int g = ((current_color >> 8) & 0xFF) * current_alpha + ((bg >> 8) & 0xFF) * (1.0 - current_alpha);
			int b = (current_color & 0xFF) * current_alpha + (bg & 0xFF) * (1.0 - current_alpha);
			
			*(unsigned int *)dst = (r << 16) | (g << 8) | b;
		}
	}
}

// Simple rotation helper (Rotates v by pitch (X) then yaw (Y))
// Assumes camera looks down -Z by default in canonical space
static t_vec3	rotate_vector(t_vec3 v, double pitch, double yaw)
{
	// Rotate X (Pitch)
	double y1 = v.y * cos(pitch) - v.z * sin(pitch);
	double z1 = v.y * sin(pitch) + v.z * cos(pitch);
	t_vec3 v1 = vec3(v.x, y1, z1);

	// Rotate Y (Yaw)
	double x2 = v1.x * cos(yaw) + v1.z * sin(yaw);
	double z2 = -v1.x * sin(yaw) + v1.z * cos(yaw);
	return (vec3(x2, v1.y, z2));
}

void	gui_render(t_gui *gui)
{
	int		y;
	int		x;
	t_ray	ray;
	t_vec3	color;
    double  fov_deg = (gui->camera) ? gui->camera->fov : 70.0;
	double	aspect_ratio = (double)gui->width / (double)gui->height;
	double	fov_rad = fov_deg * M_PI / 180.0;
	double	half_width = tan(fov_rad / 2.0);
	double	half_height = half_width / aspect_ratio;
    
    t_vec3 cam_pos = (gui->camera) ? gui->camera->pos : vec3(0, 0, 0);

	// printf("Render Start\n");

	// Pre-calculate Camera Basis Vectors to avoid 3.6 million sin/cos calls per frame
	t_vec3 forward = rotate_vector(vec3(0, 0, -1), gui->pitch, gui->yaw);
	t_vec3 right   = rotate_vector(vec3(1, 0, 0),  gui->pitch, gui->yaw);
	t_vec3 up      = rotate_vector(vec3(0, 1, 0),  gui->pitch, gui->yaw);

	y = 0;
	while (y < gui->height)
	{
		x = 0;
		while (x < gui->width)
		{
			double px = (2.0 * (x + 0.5) / gui->width - 1.0) * half_width * aspect_ratio;
			double py = (1.0 - 2.0 * (y + 0.5) / gui->height) * half_height * aspect_ratio; // Inverted Y screen space
			
			// Linear combination of basis vectors (removing sin/cos from loop)
			// dir = forward * 1.0 + right * px + up * py
			t_vec3 dir = vec3_add(forward, vec3_add(vec3_scale(right, px), vec3_scale(up, py)));
			dir = vec3_norm(dir);

			ray_init(&ray, cam_pos, dir);
			color = trace_ray(gui->bvh, &ray, gui->scene);
			put_pixel(gui, x, y, color);
			x++;
		}
		y++;
	}

	// --- PRE-RENDERING UI LAYOUT ---
	// 1. Hover Logic (Pre-calculated to decide on popup)
	t_hit h = {0};
	bool hovering = false;
	double hx = (2.0 * (gui->mouse_x + 0.5) / gui->width - 1.0) * half_width * aspect_ratio;
	double hy = (1.0 - 2.0 * (gui->mouse_y + 0.5) / gui->height) * half_height * aspect_ratio;
	t_vec3 hdir = vec3_norm(vec3_add(forward, vec3_add(vec3_scale(right, hx), vec3_scale(up, hy))));
	t_ray hray;
	ray_init(&hray, cam_pos, hdir);
	
	int hover_x = gui->mouse_x + 20;
	int hover_y = gui->mouse_y + 20;
	if (bvh_intersect(gui->bvh, &hray, &h))
	{
		hovering = true;
		if (hover_x + 220 > gui->width) hover_x -= 240;
		if (hover_y + 90 > gui->height) hover_y -= 110;
		draw_panel(gui, hover_x, hover_y, 220, 90, 0x050505, 0x00D0D0); // Cyan border
	}

	// 2. Main Controls Panel
	draw_panel(gui, 15, 15, 300, 110, 0x050505, 0xD0A000); // Gold border

	// 3. Status Panel (Pos/FOV)
	draw_panel(gui, 15, gui->height - 65, 450, 50, 0x050505, 0x444444); // Gray border

	// 4. FPS Badge
	draw_panel(gui, gui->width - 110, 15, 95, 35, 0x050505, 0x00FF00); // Green border

	// --- SUBMIT TO WINDOW ---
	mlx_put_image_to_window(gui->mlx, gui->win, gui->img, 0, 0);

	// --- DRAW TEXT OVERLAYS ---
	int txt_gold = 0xD0A000;
	int txt_white = 0xEEEEEE;
	int txt_cyan = 0x00D0D0;

	// Controls Text
	mlx_string_put(gui->mlx, gui->win, 30, 35, txt_gold, ">>> minRT SYSTEM v1.0");
	mlx_string_put(gui->mlx, gui->win, 30, 60, txt_white, "MOVE  : W A S D / SPACE / SHIFT");
	mlx_string_put(gui->mlx, gui->win, 30, 80, txt_white, "VIEW  : LMB + DRAG");
	mlx_string_put(gui->mlx, gui->win, 30, 100, txt_white, "ZOOM  : MMB + DRAG / SCROLL");

	// Status Text
	char s_pos[128], s_opt[128];
	sprintf(s_pos, "POSITION: X:%.2f Y:%.2f Z:%.2f", cam_pos.x, cam_pos.y, cam_pos.z);
	sprintf(s_opt, "FOV: %.1f | SPEED: %.2f", (double)gui->camera->fov, gui->move_speed);
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 47, txt_white, s_pos);
	mlx_string_put(gui->mlx, gui->win, 30, gui->height - 27, txt_white, s_opt);

	// FPS Text
	char fps_txt[16];
	sprintf(fps_txt, "%.1f FPS", gui->fps);
	mlx_string_put(gui->mlx, gui->win, gui->width - 100, 37, 0x00FF00, fps_txt);

	// Hover Text
	if (hovering)
	{
		char *type = "Unknown";
		t_vec3 pos = vec3(0,0,0);
		if (h.ref.type == TYPE_SPHERE) { type = "Sphere"; pos = gui->scene->spheres[h.ref.index].pos; }
		else if (h.ref.type == TYPE_PLANE) { type = "Plane"; pos = gui->scene->planes[h.ref.index].pos; }
		else if (h.ref.type == TYPE_CYLINDER) { type = "Cylinder"; pos = gui->scene->cylinders[h.ref.index].pos; }
		else if (h.ref.type == TYPE_CONE) { type = "Cone"; pos = gui->scene->cones[h.ref.index].pos; }
		
		char h_id[64], h_pos[64];
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 25, txt_cyan, "OBJECT DETECTED");
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 45, txt_white, type);
		sprintf(h_id, "ENTITY ID: %d", (int)h.ref.index);
		sprintf(h_pos, "LOC: %.1f, %.1f, %.1f", pos.x, pos.y, pos.z);
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 65, 0x888888, h_id);
		mlx_string_put(gui->mlx, gui->win, hover_x + 15, hover_y + 80, 0x888888, h_pos);
	}
}
