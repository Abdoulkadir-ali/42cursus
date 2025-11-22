/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:43:14 by abdoali          #+#    #+#             */
/*   Updated: 2025/11/12 19:43:14 by abdoali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


#include "gui.h"

void	draw_performance_display_layout(t_layout *l, t_gui *gui)
{
	char	buffer[50];
	int		total;
	int		rendered;

	gui_layout_title(l, "OPTIMIZATIONS");

	format_number(gui->fps, buffer);
	gui_layout_key_value(l, "FPS:", buffer);

	total = gui->map->width * gui->map->height;
	if (gui->render_config->lod_level > 0)
		rendered = total / (gui->render_config->lod_level * gui->render_config->lod_level);
	else
		rendered = total;
	format_number(total, buffer);
	gui_layout_key_value(l, "Total:", buffer);
	format_number(rendered, buffer);
	gui_layout_key_value(l, "Rendered:", buffer);

	format_number(gui->render_config->lod_level, buffer);
	gui_layout_key_value(l, "LOD (L):", buffer);
	format_float(gui->camera->z_scale, buffer);
	gui_layout_key_value(l, "Z-Scale (Z):", buffer);

	gui_layout_key_value(l, "Z-Divisor (X):", gui->camera->use_z_divisor ? "ON" : "OFF");
	gui_layout_key_value(l, "Invert Move (I):", gui->camera->invert_movement ? "Camera" : "Object");
	gui_layout_key_value(l, "Depth Cull (V):", gui->render_config->use_depth_culling ? "ON" : "OFF");

	format_number(gui->camera->frustum_margin, buffer);
	gui_layout_key_value(l, "Frustum (F):", buffer);
	format_number(gui->camera->dampening_threshold, buffer);
	gui_layout_key_value(l, "Depth (D):", buffer);

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
		gui_layout_key_value(l, "Fill Tri (G):", gui->render_config->fill_triangles ? "Filled" : "Wireframe");
		format_number((gui->map->width / gui->render_config->lod_level) * (gui->map->height / gui->render_config->lod_level) * 2, buffer);
		gui_layout_key_value(l, "Tri Count:", buffer);
	}
}