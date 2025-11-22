/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:20 by abdoali           ###   ########.fr       */
/*   Updated: 2025/11/22 12:52:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include <string.h>

/* Detect resize and rebuild buffer if necessary */
static void	check_gui_resize(t_gui *gui)
{
	if (!gui->window->gui_img.img || 
		gui->window->height != gui->last_win_height)
	{
		if (gui->window->gui_img.img)
			mlx_destroy_image(gui->window->mlx_ptr, gui->window->gui_img.img);
		
		/* Update tracking and re-init */
		gui->last_win_height = gui->window->height;
		init_gui_images(gui);
	}
}

/* Draw solid background rect to the image buffer */
static void	draw_rect(t_gui *gui, t_vec2 pos, t_vec2 size, int color)
{
	int		x;
	int		y;
	char	*dst;
	t_image	*img;

	img = &gui->window->gui_img;
	if (!img->img_addr) return;

	y = pos.y;
	while (y < pos.y + size.y && y < gui->window->height)
	{
		x = pos.x;
		while (x < pos.x + size.x && x < GUI_PANEL_WIDTH)
		{
			dst = img->img_addr + (y * img->img_line_len + x * (img->img_bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}

/* Draw the stripes/border */
void	draw_panel_background(t_gui *gui)
{
	t_vec2	pos;
	t_vec2	size;
	int		i;

	/* Main Background */
	pos = create_vec2(0, 0);
	size = create_vec2(GUI_PANEL_WIDTH, gui->window->height);
	draw_rect(gui, pos, size, get_gui_theme(gui->gui_style).background);

	/* Accent Border (Right side) */
	i = 0;
	while (i < 3)
	{
		pos = create_vec2(GUI_PANEL_WIDTH - 3 + i, 0);
		size = create_vec2(1, gui->window->height);
		draw_rect(gui, pos, size, get_gui_theme(gui->gui_style).accent);
		i++;
	}
}

/* Wipe the buffer clean */
void	clear_gui(t_gui *gui)
{
	int		total_bytes;
	char	*buffer;

	if (!gui->window->gui_img.img_addr) return;
	
	total_bytes = gui->window->height * gui->window->gui_img.img_line_len;
	buffer = gui->window->gui_img.img_addr;
	ft_memset(buffer, 0, total_bytes);
}

/* The Atomic Rendering Loop */
void	render_gui(t_gui *gui)
{
	t_layout	l;

	/* 1. Stability: Ensure buffer matches window */
	check_gui_resize(gui);

	/* 2. Clear: Wipe buffer and draw fresh background */
	clear_gui(gui);
	draw_panel_background(gui);

	/* 3. Blit: Push clean background to window (Erases old text) */
	mlx_put_image_to_window(gui->window->mlx_ptr, gui->window->ptr,
		gui->window->gui_img.img, 0, 0);

	/* 4. Layout: Initialize Cursor */
	gui_layout_init(&l, gui);

	/* 5. Draw Components Stack */
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
