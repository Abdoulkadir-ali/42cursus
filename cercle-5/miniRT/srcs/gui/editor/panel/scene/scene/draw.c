/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_scene_panel_text(t_gui *gui)
{
	t_vec2s	d;
	char	buf[48];
	size_t	total;

	d = gui->win.disp_size;
	if (!gui->scene_panel.visible)
		return ;
	total = 0;
	if (gui->scene)
		total = count_scene_rows(gui->scene);
	snprintf(buf, sizeof(buf), "OBJECTS  %zu", total);
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d),
		ui_sy(CRUD_PANEL_H + 8, d), COL_ACCENT, buf);
	if (!gui->scene || total == 0)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			ui_sx(16, d), ui_sy(CRUD_PANEL_H + 24, d), COL_UI_GRAY, "(empty)");
		draw_crud_buttons(gui);
		return ;
	}
	draw_scene_rows(gui);
	draw_crud_buttons(gui);
}
