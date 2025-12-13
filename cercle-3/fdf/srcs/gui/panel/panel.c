/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:28:37 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 17:00:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "gui.h"

static void	check_gui_resize(t_gui *gui)
{
	if (!gui->window->gui_img.img
		|| gui->window->height != gui->last_win_height)
	{
		if (gui->window->gui_img.img)
			mlx_destroy_image(gui->window->mlx_ptr, gui->window->gui_img.img);
		gui->last_win_height = gui->window->height;
		init_gui_images(gui);
	}
}

static void	draw_rect(t_gui *gui, t_vec2 pos, t_vec2 size, int color)
{
	int		x;
	int		y;
	char	*dst;
	t_image	*img;

	img = &gui->window->gui_img;
	if (!img->img_addr)
		return ;
	y = pos.y;
	while (y < pos.y + size.y && y < gui->window->height)
	{
		x = pos.x;
		while (x < pos.x + size.x && x < GUI_PANEL_WIDTH)
		{
			dst = img->img_addr + (y * img->img_line_len + x * (img->img_bpp
						/ 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}

void	draw_panel_background(t_gui *gui)
{
	t_vec2	pos;
	t_vec2	size;
	int		i;

	pos = create_vec2(0, 0);
	size = create_vec2(GUI_PANEL_WIDTH, gui->window->height);
	draw_rect(gui, pos, size, get_gui_theme(gui->gui_style).background);
	i = 0;
	while (i < 3)
	{
		pos = create_vec2(GUI_PANEL_WIDTH - 3 + i, 0);
		size = create_vec2(1, gui->window->height);
		draw_rect(gui, pos, size, get_gui_theme(gui->gui_style).accent);
		i++;
	}
}

void	clear_gui(t_gui *gui)
{
	int		total_bytes;
	char	*buffer;

	if (!gui->window->gui_img.img_addr)
		return ;
	total_bytes = gui->window->height * gui->window->gui_img.img_line_len;
	buffer = gui->window->gui_img.img_addr;
	ft_memset(buffer, 0, total_bytes);
}

void	redraw_gui(t_events *events)
{
	t_layout	l;
	t_gui		*gui;

	gui = &events->gui;
	check_gui_resize(gui);
	clear_gui(gui);
	draw_panel_background(gui);
	mlx_put_image_to_window(gui->window->mlx_ptr, gui->window->ptr,
		gui->window->gui_img.img, 0, 0);
	gui_layout_init(&l, gui);
	draw_controls_guide_layout(&l, gui);
	gui_layout_add_spacer(&l, 20);
	draw_performance_display_layout(&l, gui);
	gui_layout_add_spacer(&l, 20);
	draw_projection_display_layout(&l, gui);
	gui_layout_add_spacer(&l, 10);
	draw_speed_display_layout(&l, gui);
	gui_layout_add_spacer(&l, 10);
	draw_map_name_display_layout(&l, gui);
}
