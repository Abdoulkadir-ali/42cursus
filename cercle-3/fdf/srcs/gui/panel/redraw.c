/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:26:32 by abdoali          ###   ########.fr       */
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

static void	prepare_gui(t_events *events)
{
	t_gui	*gui;

	gui = &events->gui;
	check_gui_resize(gui);
	clear_gui(gui);
	draw_panel_background(gui);
}

static void	render_gui_image(t_gui *gui)
{
	mlx_put_image_to_window(gui->window->mlx_ptr, gui->window->ptr,
		gui->window->gui_img.img, 0, 0);
}

static void	draw_gui_layouts(t_gui *gui)
{
	t_layout	l;

	gui_layout_init(&l, gui);
	l.cursor_y += 40;
	draw_controls_guide_layout(&l, gui);
	gui_layout_add_spacer(&l, 20);
	draw_performance_display_layout(&l, gui);
	gui_layout_add_spacer(&l, 20);
	draw_projection_display_layout(&l, gui);
	gui_layout_add_spacer(&l, 10);
	draw_speed_display_layout(&l, gui);
	gui_layout_add_spacer(&l, 10);
	draw_map_layout(&l, gui);
	draw_transform_stats(gui);
}

void	redraw_gui(t_events *events)
{
	t_gui	*gui;

	gui = &events->gui;
	prepare_gui(events);
	render_gui_image(gui);
	draw_gui_layouts(gui);
}
