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
	// printf("Render End\n");
	mlx_put_image_to_window(gui->mlx, gui->win, gui->img, 0, 0);
	
	// UI Overlay
	int y_offset = 20;
	int txt_color = 0xFFFFFF;
	mlx_string_put(gui->mlx, gui->win, 20, y_offset, txt_color, "miniRT Controls:"); y_offset += 20;
	mlx_string_put(gui->mlx, gui->win, 20, y_offset, txt_color, "Move: W A S D"); y_offset += 20;
	mlx_string_put(gui->mlx, gui->win, 20, y_offset, txt_color, "Look: LMB + Drag"); y_offset += 20;
	mlx_string_put(gui->mlx, gui->win, 20, y_offset, txt_color, "Speed: Arrows Up/Down"); y_offset += 20;
	mlx_string_put(gui->mlx, gui->win, 20, y_offset, txt_color, "FOV: MMB + Drag (or Scroll / +/-)"); y_offset += 20;
	mlx_string_put(gui->mlx, gui->win, 20, y_offset, txt_color, "Exit: ESC"); y_offset += 20;
	
	char buf[64];
	sprintf(buf, "FOV: %.1f | Speed: %.3f | Pos: %.1f %.1f %.1f", 
		gui->camera->fov, gui->move_speed, gui->camera->pos.x, gui->camera->pos.y, gui->camera->pos.z);
	mlx_string_put(gui->mlx, gui->win, 20, y_offset, txt_color, buf);
}
