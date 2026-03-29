/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_scene_rows(t_gui *gui)
{
	int		total;
	int		row;
	int		y_px;
	t_type	ty;
	int		idx;

	total = count_scene_rows(gui->scene);
	row = 0;
	y_px = (CRUD_PANEL_H + SCENE_PANEL_PAD_Y) - gui->scene_panel->scroll;
	while (row < total && y_px < gui->win.disp_size.y - SCENE_PANEL_PAD_Y)
	{
		if (y_px >= (CRUD_PANEL_H + 4))
		{
			row_to_object(gui, row, &ty, &idx);
			draw_one_row(gui, y_px, ty, idx);
		}
		y_px += ROW_H;
		row++;
	}
}

/**
 * @brief Draws the text list of scene objects in the hierarchy panel.
 * @param gui Pointer to the GUI.
 */
void	draw_scene_panel_text(t_gui *gui)
{
	char	buf[48];
	int		total;

	if (!gui->scene_panel->visible)
		return ;
	total = 0;
	if (gui->scene)
		total = count_scene_rows(gui->scene);
	snprintf(buf, sizeof(buf), "OBJECTS  %d", total);
	gui_draw_string(gui, buf, SCENE_PANEL_HDR_X,
		CRUD_PANEL_H + SCENE_PANEL_PAD_Y, COL_ACCENT);
	if (!gui->scene || total == 0)
	{
		gui_draw_string(gui, "(empty)", 16, CRUD_PANEL_H + 24,
			SCENE_PANEL_EMPTY_COL);
		draw_crud_buttons(gui);
		return ;
	}
	draw_scene_rows(gui);
	draw_crud_buttons(gui);
}
