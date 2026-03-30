/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:56:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_scene_panel_bg(t_gui *gui)
{
	t_panel	p;
	int		w;
	int		h;

	if (!gui->scene_panel.visible)
		return ;
	w = gui->scene_panel.width;
	h = gui->win.disp_h;
	p = (t_panel){.x = 0, .y = 0, .w = w, .h = h,
		.bg = COL_BG, .brd = COL_BORDER,
		.pos = vec2i(0, 0), .size = vec2i(w, h)};
	draw_panel(gui, p);
}

void	draw_scene_panel_text(t_gui *gui)
{
	char	buf[48];
	int		total;

	if (!gui->scene_panel.visible)
		return ;
	total = gui->scene ? count_scene_rows(gui->scene) : 0;
	snprintf(buf, sizeof(buf), "OBJECTS  %d", total);
	mlx_string_put(gui->win.mlx, gui->win.win, 8,
		CRUD_PANEL_H + 8, COL_ACCENT, buf);
	if (!gui->scene || total == 0)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			16, CRUD_PANEL_H + 24, 0x505060, "(empty)");
		draw_crud_buttons(gui);
		return ;
	}
	draw_scene_rows(gui);
	draw_crud_buttons(gui);
}

bool	scene_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	int		row;
	int		total;
	t_type	ty;
	int		idx;

	if (!gui->scene_panel.visible || !gui->scene)
		return (false);
	if (mouse.x < 0 || mouse.x >= gui->scene_panel.width)
		return (false);
	if (mouse.y >= 0 && mouse.y < CRUD_PANEL_H)
		return (crud_handle_click(gui, mouse));
	row = (mouse.y - CRUD_PANEL_H + gui->scene_panel.scroll) / ROW_H;
	total = count_scene_rows(gui->scene);
	if (row < 0 || row >= total)
		return (false);
	row_to_object(gui, row, &ty, &idx);
	if (ty == TYPE_NONE)
		return (true);
	select_object(gui, ty, idx);
	gui->render.dirty = true;
	return (true);
}

bool	scene_panel_handle_scroll(t_gui *gui, int button)
{
	int	max_scroll;
	int	rows;

	if (!gui->scene_panel.visible || !gui->scene)
		return (false);
	if (gui->input.mouse_x < 0 || gui->input.mouse_x >= gui->scene_panel.width)
		return (false);
	rows = count_scene_rows(gui->scene);
	max_scroll = rows * ROW_H;
	if (button == Button4)
		gui->scene_panel.scroll -= ROW_H;
	else if (button == Button5)
		gui->scene_panel.scroll += ROW_H;
	if (gui->scene_panel.scroll < 0)
		gui->scene_panel.scroll = 0;
	if (gui->scene_panel.scroll > max_scroll)
		gui->scene_panel.scroll = max_scroll;
	return (true);
}
