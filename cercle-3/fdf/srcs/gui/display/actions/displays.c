/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 21:01:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"


static void	format_depth_str(int percent, char *str)
{
	str[0] = '0' + (percent / 10);
	str[1] = '0' + (percent % 10);
	str[2] = '%';
	str[3] = ' ';
	str[4] = 'v';
	str[5] = 'i';
	str[6] = 's';
	str[7] = 'i';
	str[8] = 'b';
	str[9] = 'l';
	str[10] = 'e';
	str[11] = '\0';
}

static void	draw_performance_header(t_data *data, int *y)
{
	put_colored(data, GUI_PADDING, *y, "OPTIMIZATIONS", GUI_TITLE_COLOR);
	*y += GUI_TITLE_HEIGHT;
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

void	draw_dampening_display(t_data *data)
{
	int		y;
	char	depth_str[20];
	int		visible_percent;

	y = data->window.height - 240;
	put_colored(data, GUI_PADDING, y, "DEPTH DAMPENING", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	if (data->camera.dampening_threshold <= data->map->min_z)
		put_value(data, GUI_PADDING + 10, y, "OFF");
	else
	{
		visible_percent = (int)(100.0 * (data->map->max_z
					- data->camera.dampening_threshold) / (data->map->max_z
					- data->map->min_z));
		format_depth_str(visible_percent, depth_str);
		put_value(data, GUI_PADDING + 10, y, depth_str);
	}
}

void	draw_style_display(t_data *data)
{
	int		y;
	int		accent;
	char	*names[GUI_STYLE_COUNT] = {"TRON BLUE", "TRON ORANGE", "MATRIX", "CYBERPUNK", "NEON GRID"};
	y = data->window.height - 240;
	accent = get_gui_theme(data->camera.gui_style).accent;
	put_colored(data, GUI_PADDING, y, "GUI STYLE", accent);
	y += GUI_TITLE_HEIGHT;
	put_colored(data, GUI_PADDING + 10, y, names[data->camera.gui_style],
		accent);
}

void	draw_projection_display_at(t_data *data, int *section_y)
{
	int		y;
	char	*names[PROJ_COUNT] = {"Isometric", "Orthographic", "Perspective", "Oblique",
		"Camera Matrix", "Nonlinear"};
	y = *section_y;
	put_colored(data, GUI_PADDING, y, "PROJECTION", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	put_value(data, GUI_PADDING + 10, y, names[data->camera.projection]);
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

void	draw_speed_display_at(t_data *data, int *section_y)
{
	int		y;
	char	move_str[10];
	char	zoom_str[10];

	y = *section_y;
	put_colored(data, GUI_PADDING, y, "SPEEDS", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Move:");
	format_speed(data->camera.move_speed, move_str);
	put_value(data, GUI_PADDING + 100, y, move_str);
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Zoom:");
	format_speed(data->camera.zoom_speed, zoom_str);
	put_value(data, GUI_PADDING + 100, y, zoom_str);
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

void	draw_map_name_display_at(t_data *data, int *section_y)
{
	int		y;
	char	*map_name;

	y = *section_y;
	put_colored(data, GUI_PADDING, y, "MAP", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	if (data->graphics.map_manager.map_files && data->graphics.map_manager.current_index >= 0
		&& data->graphics.map_manager.current_index < data->graphics.map_manager.count)
	{
		map_name = data->graphics.map_manager.map_files[data->graphics.map_manager.current_index];
		put_value(data, GUI_PADDING + 10, y, map_name);
	}
	else
		put_value(data, GUI_PADDING + 10, y, "Test Grid");
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

void	draw_performance_display_at(t_data *data, int *section_y)
{
	int		y;
	char	buffer[50];

	y = *section_y;
	draw_performance_header(data, &y);
	draw_performance_counts(data, &y, buffer);
	draw_performance_lod_zscale(data, &y, buffer);
	draw_performance_strings(data, &y);
	draw_performance_numbers(data, &y, buffer);
	draw_performance_algorithm(data, &y, buffer);
	*section_y = y;
}
