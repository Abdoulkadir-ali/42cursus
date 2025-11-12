/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:25:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

#include <mlx.h>

static void	gui_pixel_put(t_gui *gui, t_vec2 pos, int color)
{
	char	*dst;

	if (pos.x < 0 || pos.x >= GUI_PANEL_WIDTH || pos.y < 0 || pos.y >= gui->window->height)
		return ;
	dst = gui->window->gui_img.img_addr + ((int)pos.y * gui->window->gui_img.img_line_len + (int)pos.x * (gui->window->gui_img.img_bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_rect(t_gui *gui, t_vec2 pos, t_vec2 size, int color)
{
	int	x;
	int	y;

	y = (int)pos.y;
	while (y < (int)pos.y + (int)size.y && y < gui->window->height)
	{
		x = (int)pos.x;
		while (x < (int)pos.x + (int)size.x && x < GUI_PANEL_WIDTH)
		{
			t_vec2 pixel_pos = create_vec2(x, y);
			gui_pixel_put(gui, pixel_pos, color);
			x++;
		}
		y++;
	}
}

void	draw_panel_background(t_gui *gui)
{
	t_vec2	pos;
	t_vec2	size;
	int		bg_color;
	int		accent;
	int		i;

	bg_color = get_gui_theme(gui->gui_style).background;
	accent = get_gui_theme(gui->gui_style).accent;
	pos = create_vec2(0, 0);
	size = create_vec2(GUI_PANEL_WIDTH, gui->window->height);
	draw_rect(gui, pos, size, bg_color);
	i = 0;
	while (i < 3)
	{
		pos = create_vec2(GUI_PANEL_WIDTH - 3 + i, 0);
		size = create_vec2(1, gui->window->height);
		draw_rect(gui, pos, size, accent);
		i++;
	}
}

void	render_gui(t_gui *gui)
{
	int	section_y;

	section_y = GUI_PADDING;
	draw_controls_guide_at(gui, &section_y);
	section_y += 20;
	draw_performance_display_at(gui, &section_y);
	section_y = gui->window->height - 220;
	draw_projection_display_at(gui, &section_y);
	section_y += 10;
	draw_speed_display_at(gui, &section_y);
	section_y += 10;
	draw_map_name_display_at(gui, &section_y);
}
