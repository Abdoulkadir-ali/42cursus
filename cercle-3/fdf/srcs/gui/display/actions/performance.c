/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:26:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 14:26:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


static void	draw_performance_header(t_data *data, int *y)
{
	put_colored(&data->gui, GUI_PADDING, *y, (t_colored_text){"OPTIMIZATIONS", GUI_TITLE_COLOR});
	*y += GUI_TITLE_HEIGHT;
}

static void	draw_fps(t_data *data, int *y)
{
	char	buffer[20];

	put_text(data, GUI_PADDING + 140, *y, "FPS:");
	format_number(data->gui.fps, buffer);
	put_value(data, GUI_PADDING + 180, *y, buffer);
}

static void	draw_performance_counts(t_data *data, int *y, char *buffer)
{
	int		total;
	int		rendered;

	total = data->map->width * data->map->height;
	if (data->graphics.render_config.lod_level > 0)
		rendered = total / (data->graphics.render_config.lod_level * data->graphics.render_config.lod_level);
	else
		rendered = total;
	put_text(data, GUI_PADDING, *y, "Total:");
	format_number(total, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, *y, "Rendered:");
	format_number(rendered, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT + 5;
}

static void	draw_performance_lod_zscale(t_data *data, int *y, char *buffer)
{
	put_text(data, GUI_PADDING, *y, "LOD (L):");
	format_number(data->graphics.render_config.lod_level, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, *y, "Z-Scale (Z):");
	format_float(data->camera.z_scale, buffer);
	put_value(data, GUI_PADDING + 120, *y, buffer);
	*y += GUI_LINE_HEIGHT;
}

static void	draw_performance_strings(t_data *data, int *y)
{
	const char *string_labels[] = {"Z-Divisor (X):", "Invert Move (I):", "Depth Cull (V):"};
	const char *string_values[] = {
		data->camera.use_z_divisor ? "ON" : "OFF",
		data->camera.invert_movement ? "Camera" : "Object",
		data->graphics.render_config.use_depth_culling ? "ON" : "OFF"
	};
	int i = 0;
	while (i < 3)
	{
		put_text(data, GUI_PADDING, *y, string_labels[i]);
		put_value(data, GUI_PADDING + 120, *y, string_values[i]);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
}

static void	draw_performance_numbers(t_data *data, int *y, char *buffer)
{
	const char *format_labels[] = {"Frustum (F):", "Depth (D):"};
	int format_values[] = {data->camera.frustum_margin, data->camera.dampening_threshold};
	int i = 0;
	while (i < 2)
	{
		put_text(data, GUI_PADDING, *y, format_labels[i]);
		format_number(format_values[i], buffer);
		put_value(data, GUI_PADDING + 120, *y, buffer);
		*y += GUI_LINE_HEIGHT;
		i++;
	}
}

static void	draw_performance_algorithm(t_data *data, int *y, char *buffer)
{
	put_text(data, GUI_PADDING, *y, "Algorithm (A):");
	if (data->graphics.render_config.render_mode == RENDER_LINES)
		put_value(data, GUI_PADDING + 120, *y, "Lines");
	else if (data->graphics.render_config.render_mode == RENDER_SPLINES)
		put_value(data, GUI_PADDING + 120, *y, "Splines");
	else
		put_value(data, GUI_PADDING + 120, *y, "Triangles");
	*y += GUI_LINE_HEIGHT;
	if (data->graphics.render_config.render_mode == RENDER_SPLINES)
	{
		put_text(data, GUI_PADDING, *y, "Segments (T):");
		format_number(data->camera.spline_segments, buffer);
		put_value(data, GUI_PADDING + 120, *y, buffer);
		*y += GUI_LINE_HEIGHT;
	}
	else if (data->graphics.render_config.render_mode == RENDER_TRIANGLES)
	{
		put_text(data, GUI_PADDING, *y, "Fill Tri (G):");
		put_value(data, GUI_PADDING + 120, *y,
			data->graphics.render_config.fill_triangles ? "Filled" : "Wireframe");
		*y += GUI_LINE_HEIGHT;
		put_text(data, GUI_PADDING, *y, "Tri Count:");
		format_number((data->map->width / data->graphics.render_config.lod_level) * (data->map->height
				/ data->graphics.render_config.lod_level) * 2, buffer);
		put_value(data, GUI_PADDING + 120, *y, buffer);
		*y += GUI_LINE_HEIGHT;
	}
}

void	draw_performance_display_at(t_data *data, int *section_y)
{
	int		y;
	char	buffer[50];

	y = *section_y;
	draw_performance_header(data, &y);
	draw_fps(data, &y);
	draw_performance_counts(data, &y, buffer);
	draw_performance_lod_zscale(data, &y, buffer);
	draw_performance_strings(data, &y);
	draw_performance_numbers(data, &y, buffer);
	draw_performance_algorithm(data, &y, buffer);
	*section_y = y;
}