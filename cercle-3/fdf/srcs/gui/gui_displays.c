/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_displays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:22:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gui.h"
#include "projection.h"

static void	put_text(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_TEXT_COLOR, text);
}

static void	put_colored(t_data *d, int x, int y, char *text, int color)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, color, text);
}

static void	put_value(t_data *data, int x, int y, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, GUI_VALUE_COLOR, text);
}

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

void	draw_dampening_display(t_data *data)
{
	int		y;
	char	depth_str[20];
	int		visible_percent;

	y = data->win_height - 240;
	put_colored(data, GUI_PADDING, y, "DEPTH DAMPENING", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	if (data->camera.dampening_threshold <= data->map->min_z)
		put_value(data, GUI_PADDING + 10, y, "OFF");
	else
	{
		visible_percent = (int)(100.0 * (data->map->max_z
					- data->camera.dampening_threshold)
				/ (data->map->max_z - data->map->min_z));
		format_depth_str(visible_percent, depth_str);
		put_value(data, GUI_PADDING + 10, y, depth_str);
	}
}

void	draw_style_display(t_data *data)
{
	int		y;
	int		accent;

	y = data->win_height - 240;
	accent = get_gui_accent_color(data->camera.gui_style);
	put_colored(data, GUI_PADDING, y, "GUI STYLE", accent);
	y += GUI_TITLE_HEIGHT;
	put_colored(data, GUI_PADDING + 10, y,
		(char *)g_gui_style_names[data->camera.gui_style], accent);
}

void	draw_projection_display_at(t_data *data, int *section_y)
{
	int	y;

	y = *section_y;
	put_colored(data, GUI_PADDING, y, "PROJECTION", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	put_value(data, GUI_PADDING + 10, y,
		(char *)g_projection_names[data->camera.projection]);
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

static void	format_speed(double speed, char *buffer)
{
	int	whole;
	int	decimal;

	whole = (int)speed;
	decimal = (int)((speed - whole) * 100);
	buffer[0] = '0' + (whole / 10);
	buffer[1] = '0' + (whole % 10);
	buffer[2] = '.';
	buffer[3] = '0' + (decimal / 10);
	buffer[4] = '0' + (decimal % 10);
	buffer[5] = 'x';
	buffer[6] = '\0';
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
	if (data->map_files && data->current_map_index >= 0
		&& data->current_map_index < data->map_count)
	{
		map_name = data->map_files[data->current_map_index];
		put_value(data, GUI_PADDING + 10, y, map_name);
	}
	else
		put_value(data, GUI_PADDING + 10, y, "Test Grid");
	y += GUI_LINE_HEIGHT;
	*section_y = y;
}

static void	format_number(int num, char *buffer)
{
	int	i;
	int	temp;

	if (num == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return ;
	}
	i = 0;
	temp = num;
	while (temp > 0)
	{
		buffer[i++] = '0' + (temp % 10);
		temp /= 10;
	}
	buffer[i] = '\0';
	temp = 0;
	while (temp < i / 2)
	{
		buffer[temp] ^= buffer[i - 1 - temp];
		buffer[i - 1 - temp] ^= buffer[temp];
		buffer[temp] ^= buffer[i - 1 - temp];
		temp++;
	}
}

static void	format_float(double val, char *buffer)
{
	int	whole;
	int	decimal;
	int	i;

	whole = (int)val;
	decimal = (int)((val - whole) * 10);
	if (decimal < 0)
		decimal = -decimal;
	i = 0;
	if (whole >= 10)
		buffer[i++] = '0' + (whole / 10);
	buffer[i++] = '0' + (whole % 10);
	buffer[i++] = '.';
	buffer[i++] = '0' + decimal;
	buffer[i] = '\0';
}

void	draw_performance_display_at(t_data *data, int *section_y)
{
	int		y;
	char	buffer[50];
	int		total;
	int		rendered;

	y = *section_y;
	put_colored(data, GUI_PADDING, y, "OPTIMIZATIONS", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	total = data->map->width * data->map->height;
	if (data->lod_level > 0)
		rendered = total / (data->lod_level * data->lod_level);
	else
		rendered = total;
	put_text(data, GUI_PADDING, y, "Total:");
	format_number(total, buffer);
	put_value(data, GUI_PADDING + 120, y, buffer);
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Rendered:");
	format_number(rendered, buffer);
	put_value(data, GUI_PADDING + 120, y, buffer);
	y += GUI_LINE_HEIGHT + 5;
	put_text(data, GUI_PADDING, y, "LOD (L):");
	format_number(data->lod_level, buffer);
	put_value(data, GUI_PADDING + 120, y, buffer);
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Z-Scale (Z):");
	format_float(data->camera.z_scale, buffer);
	put_value(data, GUI_PADDING + 120, y, buffer);
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Z-Divisor (X):");
	put_value(data, GUI_PADDING + 120, y, data->camera.use_z_divisor ? "ON" : "OFF");
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Invert Move (I):");
	put_value(data, GUI_PADDING + 120, y, data->camera.invert_movement ? "Camera" : "Object");
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Depth Cull (V):");
	put_value(data, GUI_PADDING + 120, y, data->use_depth_culling ? "ON" : "OFF");
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Frustum (F):");
	format_number(data->camera.frustum_margin, buffer);
	put_value(data, GUI_PADDING + 120, y, buffer);
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Depth (D):");
	format_number(data->camera.dampening_threshold, buffer);
	put_value(data, GUI_PADDING + 120, y, buffer);
	y += GUI_LINE_HEIGHT;
	put_text(data, GUI_PADDING, y, "Algorithm (A):");
	if (data->render_mode == RENDER_LINES)
		put_value(data, GUI_PADDING + 120, y, "Lines");
	else if (data->render_mode == RENDER_SPLINES)
		put_value(data, GUI_PADDING + 120, y, "Splines");
	else
		put_value(data, GUI_PADDING + 120, y, "Triangles");
	y += GUI_LINE_HEIGHT;
	if (data->render_mode == RENDER_SPLINES)
	{
		put_text(data, GUI_PADDING, y, "Segments (T):");
		format_number(data->camera.spline_segments, buffer);
		put_value(data, GUI_PADDING + 120, y, buffer);
		y += GUI_LINE_HEIGHT;
	}
	else if (data->render_mode == RENDER_TRIANGLES)
	{
		put_text(data, GUI_PADDING, y, "Tri Count:");
		format_number((data->map->width / data->lod_level) *
			(data->map->height / data->lod_level) * 2, buffer);
		put_value(data, GUI_PADDING + 120, y, buffer);
		y += GUI_LINE_HEIGHT;
	}
	*section_y = y;
}
