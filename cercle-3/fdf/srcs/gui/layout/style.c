/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:55 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:29:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_dampening_display(t_gui *gui)
{
	int		y;
	char	depth_str[20];
	int		visible_percent;

	y = gui->window->height - 240;
	put_colored(gui, GUI_PADDING, y, (t_colored_text){"DEPTH DAMPENING",
		GUI_TITLE_COLOR});
	y += GUI_TITLE_HEIGHT;
	if ((int)gui->camera->dampening_threshold <= gui->map->min_max_z.x)
		put_value(gui, GUI_PADDING + 10, y, "OFF");
	else
	{
		visible_percent = (int)(100.0 * (gui->map->min_max_z.y
					- gui->camera->dampening_threshold) / (gui->map->min_max_z.y
					- gui->map->min_max_z.x));
		format_depth_str(visible_percent, depth_str);
		put_value(gui, GUI_PADDING + 10, y, depth_str);
	}
}

void	draw_style_display(t_gui *gui)
{
	int		y;
	int		accent;
	char	*names[GUI_STYLE_COUNT];

	names[0] = "TRON BLUE";
	names[1] = "TRON ORANGE";
	names[2] = "MATRIX";
	names[3] = "CYBERPUNK";
	names[4] = "NEON GRID";
	y = gui->window->height - 240;
	accent = get_gui_theme(gui->gui_style).accent;
	put_colored(gui, GUI_PADDING, y, (t_colored_text){"GUI STYLE", accent});
	y += GUI_TITLE_HEIGHT;
	put_colored(gui, GUI_PADDING + 10, y,
		(t_colored_text){names[gui->gui_style], accent});
}
