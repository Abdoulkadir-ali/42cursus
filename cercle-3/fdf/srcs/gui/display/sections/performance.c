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


static void	draw_performance_header(t_gui *gui, int *y)
{
	put_colored(gui, GUI_PADDING, *y, (t_colored_text){"OPTIMIZATIONS", GUI_TITLE_COLOR});
	*y += GUI_TITLE_HEIGHT;
}

static void	draw_performance_counts(t_gui *gui, int *y, char *buffer)
{
	int		total;
	int		rendered;

	total = gui->map->width * gui->map->height;
	if (gui->render_config->lod_level > 0)
		rendered = total / (gui->render_config->lod_level * gui->render_config->lod_level);
	else
		rendered = total;
	put_text(gui, GUI_PADDING, *y, "Total:");
	format_number(total, buffer);
	put_value(gui, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
	put_text(gui, GUI_PADDING, *y, "Rendered:");
	format_number(rendered, buffer);
	put_value(gui, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT + 5;
}

static void	draw_performance_lod_zscale(t_gui *gui, int *y, char *buffer)
{
	put_text(gui, GUI_PADDING, *y, "LOD (L):");
	format_number(gui->render_config->lod_level, buffer);
	put_value(gui, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
	put_text(gui, GUI_PADDING, *y, "Z-Scale (Z):");
	format_float(gui->camera->z_scale, buffer);
	put_value(gui, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
}

static void	draw_performance_strings(t_gui *gui, int *y)
{
	const char *string_labels[] = {"Z-Divisor (X):", "Invert Move (I):", "Depth Cull (V):"};
	const char *string_values[] = {
		gui->camera->use_z_divisor ? "ON" : "OFF",
		gui->camera->invert_movement ? "Camera" : "Object",
		gui->render_config->use_depth_culling ? "ON" : "OFF"
	};
	int i = 0;
	while (i < 3)
	{
		put_text(gui, GUI_PADDING, *y, (char *)string_labels[i]);
		put_value(gui, GUI_PADDING + 120, *y, (char *)string_values[i]);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
}

static void	draw_performance_numbers(t_gui *gui, int *y, char *buffer)
{
	const char *format_labels[] = {"Frustum (F):", "Depth (D):"};
	int format_values[] = {gui->camera->frustum_margin, gui->camera->dampening_threshold};
	int i = 0;
	while (i < 2)
	{
		put_text(gui, GUI_PADDING, *y, (char *)format_labels[i]);
		format_number(format_values[i], buffer);
		put_value(gui, GUI_PADDING + 120, *y, buffer);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
}

static void	draw_performance_algorithm(t_gui *gui, int *y, char *buffer)
{
	put_text(gui, GUI_PADDING, *y, "Algorithm (A):");
	if (gui->render_config->render_mode == RENDER_LINES)
		put_value(gui, GUI_PADDING + 120, *y, "Lines");
	else if (gui->render_config->render_mode == RENDER_SPLINES)
		put_value(gui, GUI_PADDING + 120, *y, "Splines");
	else
		put_value(gui, GUI_PADDING + 120, *y, "Triangles");
	*y += GUI_LINE_HEIGHT;
	if (gui->render_config->render_mode == RENDER_SPLINES)
	{
		put_text(gui, GUI_PADDING, *y, "Segments (T):");
		format_number(gui->camera->spline_segments, buffer);
		put_value(gui, GUI_PADDING + 120, *y, buffer);
		*y += GUI_LINE_HEIGHT;
	}
	else if (gui->render_config->render_mode == RENDER_TRIANGLES)
	{
		put_text(gui, GUI_PADDING, *y, "Fill Tri (G):");
		put_value(gui, GUI_PADDING + 120, *y,
			gui->render_config->fill_triangles ? "Filled" : "Wireframe");
		*y += GUI_LINE_HEIGHT;
		put_text(gui, GUI_PADDING, *y, "Tri Count:");
		format_number((gui->map->width / gui->render_config->lod_level) * (gui->map->height
				/ gui->render_config->lod_level) * 2, buffer);
		put_value(gui, GUI_PADDING + 120, *y, buffer);
		*y += GUI_LINE_HEIGHT;
	}
}

void	draw_performance_display_at(t_gui *gui, int *section_y)
{
	int		y;
	char	buffer[50];

	y = *section_y;
	draw_performance_header(gui, &y);
	draw_performance_counts(gui, &y, buffer);
	draw_performance_lod_zscale(gui, &y, buffer);
	draw_performance_strings(gui, &y);
	draw_performance_numbers(gui, &y, buffer);
	draw_performance_algorithm(gui, &y, buffer);
	*section_y = y;
}