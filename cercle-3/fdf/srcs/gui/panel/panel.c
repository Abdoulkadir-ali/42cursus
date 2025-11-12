/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:29:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "data.h"
#include <mlx.h>

static void	gui_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= GUI_PANEL_WIDTH || y < 0 || y >= data->win_height)
		return ;
	dst = data->gui_addr + (y * data->gui_line_len + x * (data->gui_bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_rect(t_data *data, int pos_x, int pos_y, int size_x, int size_y, int color)
{
	int	x;
	int	y;

	y = pos_y;
	while (y < pos_y + size_y && y < data->win_height)
	{
		x = pos_x;
		while (x < pos_x + size_x && x < GUI_PANEL_WIDTH)
		{
			gui_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_panel_background(t_data *data)
{
	int	pos_x;
	int	pos_y;
	int	size_x;
	int	size_y;
	int		bg_color;
	int		accent;
	int		i;

	bg_color = get_gui_background_color(data->camera.gui_style);
	accent = get_gui_accent_color(data->camera.gui_style);
	pos_x = 0;
	pos_y = 0;
	size_x = GUI_PANEL_WIDTH;
	size_y = data->win_height;
	draw_rect(data, pos_x, pos_y, size_x, size_y, bg_color);
	i = 0;
	while (i < 3)
	{
		pos_x = GUI_PANEL_WIDTH - 3 + i;
		size_x = 1;
		size_y = data->win_height;
		draw_rect(data, pos_x, pos_y, size_x, size_y, accent);
		i++;
	}
}

void	render_gui(t_data *data)
{
	int	section_y;

	section_y = GUI_PADDING;
	draw_controls_guide_at(data, &section_y);
	section_y += 20;
	draw_performance_display_at(data, &section_y);
	section_y = data->win_height - 220;
	draw_projection_display_at(data, &section_y);
	section_y += 10;
	draw_speed_display_at(data, &section_y);
	section_y += 10;
	draw_map_name_display_at(data, &section_y);
}

int	init_gui(t_data *data)
{
	data->gui_img = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
	if (!data->gui_img)
		return (0);
	data->gui_addr = mlx_get_data_addr(data->gui_img, &data->gui_bpp, &data->gui_line_len, &data->gui_endian);
	return (1);
}
