/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "gui.h"

/**
 * @brief Draws the background panel for the scene hierarchy.
 * @param gui Pointer to the GUI.
 */
void	draw_scene_panel_bg(t_gui *gui)
{
	t_panel	panel;
	int		w;
	int		h;

	if (!gui->scene_panel.visible)
		return ;
	w = gui->scene_panel.width;
	h = gui->win.disp_h;
	panel = (t_panel){.x = 0, .y = 0, .w = w, .h = h, .bg = COL_BG,
		.brd = COL_BORDER, .pos = vec2i(0, 0), .size = vec2i(w, h)};
	draw_panel(gui, panel);
}

static void	draw_scene_rows(t_gui *gui)
{
	int		total;
	int		row;
	int		y_px;
	t_type	ty;
	int		idx;

	total = count_scene_rows(gui->scene);
	row = 0;
	y_px = (CRUD_PANEL_H + SCENE_PANEL_PAD_Y) - gui->scene_panel.scroll;
	while (row < total && y_px < gui->win.disp_h - SCENE_PANEL_PAD_Y)
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

	if (!gui->scene_panel.visible)
		return ;
	total = gui->scene ? count_scene_rows(gui->scene) : 0;
	snprintf(buf, sizeof(buf), "OBJECTS  %d", total);
	mlx_string_put(gui->win.mlx, gui->win.win, SCENE_PANEL_HDR_X,
		CRUD_PANEL_H + SCENE_PANEL_PAD_Y, COL_ACCENT, buf);
	if (!gui->scene || total == 0)
	{
		mlx_string_put(gui->win.mlx, gui->win.win, 16,
			CRUD_PANEL_H + 24, SCENE_PANEL_EMPTY_COL, "(empty)");
		draw_crud_buttons(gui);
		return ;
	}
	draw_scene_rows(gui);
	draw_crud_buttons(gui);
}
