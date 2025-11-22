/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 12:52:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	gui_pixel_put(t_gui *gui, int x, int y, int color)
{
	char	*dst;
	t_image	*img;
	int		height;

	img = &gui->window->gui_img;
	height = gui->window->height;
	if (x < 0 || x >= GUI_PANEL_WIDTH || y < 0 || y >= height)
		return ;
	dst = img->img_addr + (y * img->img_line_len + x * (img->img_bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_rect(t_gui *gui, t_vec2 pos, t_vec2 size, int color)
{
	int	x;
	int	y;
	int	height;

	height = gui->window->height;
	y = pos.y;
	while (y < pos.y + size.y && y < height)
	{
		x = pos.x;
		while (x < pos.x + size.x && x < GUI_PANEL_WIDTH)
			gui_pixel_put(gui, x++, y, color);
		y++;
	}
}

void	draw_panel_background(t_gui *gui)
{
	t_vec2	pos;
	t_vec2	size;
	int		height;
	int		i;

	height = gui->window->height;
	pos = create_vec2(0, 0);
	size = create_vec2(GUI_PANEL_WIDTH, height);
	draw_rect(gui, pos, size, get_gui_theme(gui->gui_style).background);
	i = 0;
	while (i < 3)
	{
		pos = create_vec2(GUI_PANEL_WIDTH - 3 + i++, 0);
		size = create_vec2(1, height);
		draw_rect(gui, pos, size, get_gui_theme(gui->gui_style).accent);
	}
}

void	render_gui(t_gui *gui)
{
	int	section_y;
	int	height;
	int	footer_start;

	height = gui->window->height;
	section_y = GUI_PADDING;
	draw_controls_guide_at(gui, &section_y);
	section_y += 20;
	draw_performance_display_at(gui, &section_y);
	footer_start = height - 220;
	if (section_y < footer_start)
		section_y = footer_start;
	else
		section_y += 20; // Add padding if content pushed past the footer mark
	draw_projection_display_at(gui, &section_y);
	section_y += 10;
	draw_speed_display_at(gui, &section_y);
	section_y += 10;
	draw_map_name_display_at(gui, &section_y);
}
