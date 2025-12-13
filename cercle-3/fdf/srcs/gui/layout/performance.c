/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 16:50:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	display_fps_stats(t_layout *l, t_gui *gui, char *buffer)
{
	int		total;
	int		rendered;

	format_number(gui->fps, buffer);
	gui_layout_key_value(l, "FPS:", buffer);
	total = gui->map->width * gui->map->height;
	if (gui->render_config->lod_level > 0)
		rendered = total / (gui->render_config->lod_level
				* gui->render_config->lod_level);
	else
		rendered = total;
	format_number(total, buffer);
	gui_layout_key_value(l, "Total:", buffer);
	format_number(rendered, buffer);
	gui_layout_key_value(l, "Rendered:", buffer);
}

static void	display_scale_options(t_layout *l, t_gui *gui, char *buffer)
{
	format_number(gui->render_config->lod_level, buffer);
	gui_layout_key_value(l, "LOD (L):", buffer);
	format_float(gui->camera->z_scale, buffer);
	gui_layout_key_value(l, "Z-Scale (Z):", buffer);
}

static void	display_toggle_options(t_layout *l, t_gui *gui, char *buffer)
{
	if (gui->camera->use_z_divisor)
		gui_layout_key_value(l, "Z-Divisor (X):", "ON");
	else
		gui_layout_key_value(l, "Z-Divisor (X):", "OFF");
	if (gui->camera->invert_movement)
		gui_layout_key_value(l, "Invert Move (I):", "Camera");
	else
		gui_layout_key_value(l, "Invert Move (I):", "Object");
	if (gui->render_config->use_depth_culling)
		gui_layout_key_value(l, "Depth Cull (V):", "ON");
	else
		gui_layout_key_value(l, "Depth Cull (V):", "OFF");
	format_number(gui->camera->frustum_margin, buffer);
	gui_layout_key_value(l, "Frustum (F):", buffer);
	format_number(gui->camera->dampening_threshold, buffer);
	gui_layout_key_value(l, "Depth (D):", buffer);
}

static void	display_algorithm_info(t_layout *l, t_gui *gui, char *buffer)
{
	if (gui->render_config->render_mode == RENDER_LINES)
		gui_layout_key_value(l, "Algorithm (A):", "Lines");
	else if (gui->render_config->render_mode == RENDER_SPLINES)
	{
		gui_layout_key_value(l, "Algorithm (A):", "Splines");
		format_number(gui->camera->spline_segments, buffer);
		gui_layout_key_value(l, "Segments (T):", buffer);
	}
	else
	{
		gui_layout_key_value(l, "Algorithm (A):", "Triangles");
		if (gui->render_config->fill_triangles)
			gui_layout_key_value(l, "Fill Tri (G):", "Filled");
		else
			gui_layout_key_value(l, "Fill Tri (G):", "Wireframe");
		format_number((gui->map->width / gui->render_config->lod_level)
			* (gui->map->height / gui->render_config->lod_level) * 2, buffer);
		gui_layout_key_value(l, "Tri Count:", buffer);
	}
}

void	draw_performance_display_layout(t_layout *l, t_gui *gui)
{
	char	buffer[50];

	gui_layout_title(l, "OPTIMIZATIONS");
	display_fps_stats(l, gui, buffer);
	display_scale_options(l, gui, buffer);
	display_toggle_options(l, gui, buffer);
	display_algorithm_info(l, gui, buffer);
}
