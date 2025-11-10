/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_panel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 19:40:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gui.h"
#include "projection.h"

static int	get_accent_color(t_data *data)
{
	return (get_gui_accent_color(data->camera.gui_style));
}

int	init_gui(t_data *data)
{
	data->gui_img = mlx_new_image(data->mlx_ptr, GUI_PANEL_WIDTH,
			data->win_height);
	if (!data->gui_img)
		return (0);
	data->gui_addr = mlx_get_data_addr(data->gui_img, &data->gui_bpp,
			&data->gui_line_len, &data->gui_endian);
	if (!data->gui_addr)
		return (0);
	return (1);
}

static void	gui_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= GUI_PANEL_WIDTH || y < 0 || y >= data->win_height)
		return ;
	dst = data->gui_addr + (y * data->gui_line_len + x * (data->gui_bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_rect(t_data *data, t_vec2 pos, t_vec2 size, int color)
{
	int	x;
	int	y;

	y = pos.y;
	while (y < pos.y + size.y && y < data->win_height)
	{
		x = pos.x;
		while (x < pos.x + size.x && x < GUI_PANEL_WIDTH)
		{
			gui_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_panel_background(t_data *data)
{
	t_vec2	pos;
	t_vec2	size;
	int		bg_color;
	int		accent;
	int		i;

	bg_color = get_gui_background_color(data->camera.gui_style);
	accent = get_accent_color(data);
	pos.x = 0;
	pos.y = 0;
	size.x = GUI_PANEL_WIDTH;
	size.y = data->win_height;
	draw_rect(data, pos, size, bg_color);
	i = 0;
	while (i < 3)
	{
		pos.x = GUI_PANEL_WIDTH - 3 + i;
		size.x = 1;
		size.y = data->win_height;
		draw_rect(data, pos, size, accent);
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
