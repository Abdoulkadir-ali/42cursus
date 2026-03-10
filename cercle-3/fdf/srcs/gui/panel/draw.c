/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:51:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Fill a rectangular region inside the GUI image buffer.
 * @param gui GUI object owning the destination image.
 * @param pos Top-left rectangle position.
 * @param size Rectangle size in pixels.
 * @param color Fill color written to the buffer.
 */
void	draw_rect(t_gui *gui, t_vec2 pos, t_vec2 size, int color)
{
	int		x;
	int		y;
	char	*dst;
	t_image	*img;

	img = &gui->window->gui_img;
	if (!img->img_addr)
		return ;
	y = pos.y;
	while (y < pos.y + size.y && y < (int)gui->window->height)
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

/**
 * @brief Draw the panel background and its right-edge accent border.
 * @param gui GUI object providing theme colors and window size.
 */
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
