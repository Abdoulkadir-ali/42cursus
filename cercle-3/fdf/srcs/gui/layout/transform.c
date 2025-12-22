/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 11:58:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	display_pos_stats(t_layout *l, t_gui *gui, char *buffer)
{
	format_number((int)gui->camera->offset.x, buffer);
	gui_layout_key_value(l, "Offset X:", buffer);
	format_number((int)gui->camera->offset.y, buffer);
	gui_layout_key_value(l, "Offset Y:", buffer);
}

static int	normalize_angle(double radians)
{
	int	degrees;

	degrees = (int)(radians * 180.0 / M_PI);
	degrees = degrees % 360;
	if (degrees < 0)
		degrees += 360;
	return (degrees);
}

static void	display_rot_stats(t_layout *l, t_gui *gui, char *buffer)
{
	int rot_x;
	int rot_y;
	int rot_z;

	rot_x = normalize_angle(gui->camera->rotation.x);
	rot_y = normalize_angle(gui->camera->rotation.y);
	rot_z = normalize_angle(gui->camera->rotation.z);
	format_number(rot_x, buffer);
	gui_layout_key_value(l, "Rot X (deg):", buffer);
	format_number(rot_y, buffer);
	gui_layout_key_value(l, "Rot Y (deg):", buffer);
	format_number(rot_z, buffer);
	gui_layout_key_value(l, "Rot Z (deg):", buffer);
}

static void	display_scale_stats(t_layout *l, t_gui *gui, char *buffer)
{
	format_float(gui->camera->scale, buffer);
	gui_layout_key_value(l, "Scale:", buffer);
}

static void	display_fps_stats(t_layout *l, t_gui *gui, char *buffer)
{
	format_number(gui->fps, buffer);
	gui_layout_key_value(l, "FPS:", buffer);
}

void	draw_transform_stats(t_gui *gui)
{
	t_layout	l;
	char		buffer[50];

	l.gui = gui;
	l.x_start = gui->window->width - 220; 
	l.panel_width = 200;
	l.cursor_y = 20;
	l.padding = 5;
	gui_layout_title(&l, "STATS");
	display_fps_stats(&l, gui, buffer);
	gui_layout_title(&l, "TRANSFORM");
	display_pos_stats(&l, gui, buffer);
	display_rot_stats(&l, gui, buffer);
	display_scale_stats(&l, gui, buffer);
}
