/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:39:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_transform_stats(t_gui *gui)
{
	t_layout	l;
	char		buffer[50];

	l.gui = gui;
	l.x_start = gui->window->width - 220;
	l.panel_width = 200;
	l.cursor_y = 20;
	l.padding = 5;
	gui_layout_title(&l, "STATS");
	display_fps_stats(&l, gui, buffer);
	gui_layout_title(&l, "TRANSFORM");
	display_pos_stats(&l, gui, buffer);
	display_rot_stats(&l, gui, buffer);
	display_scale_stats(&l, gui, buffer);
}
