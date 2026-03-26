/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
void	draw_popup_mesh_fmt(t_gui *gui)
{
	int	bw;

	draw_modal_bg(gui);
	mlx_string_put(gui->win.mlx, gui->win.win, gui->crud->pos.x + POPUP_PAD,
		gui->crud->pos.y + POPUP_PAD, COL_ACCENT, "Add Mesh \x2D Format");
	bw = (POPUP_W - POPUP_PAD * 3) / 2;
	draw_popup_btn(gui, vec2i(gui->crud->pos.x + POPUP_PAD,
		gui->crud->pos.y + 36 + POPUP_PAD), vec2i(bw, POPUP_ITEM_H), "OBJ",
		COL_POPUP_BTN);
	draw_popup_btn(gui, vec2i(gui->crud->pos.x + POPUP_PAD * 2 + bw,
		gui->crud->pos.y + 36 + POPUP_PAD), vec2i(bw, POPUP_ITEM_H), "GLB",
		COL_POPUP_BTN);
	draw_popup_btn(gui, vec2i(gui->crud->pos.x + POPUP_PAD,
		gui->crud->pos.y + gui->crud->h - 36), vec2i(80, 26), "\x21\x90 Back",
		COL_POPUP_BTN);
	draw_popup_btn(gui, vec2i(gui->crud->pos.x + POPUP_W - 90 - POPUP_PAD,
		gui->crud->pos.y + gui->crud->h - 36), vec2i(90, 26), "Cancel",
		COL_POPUP_BTN_CANCEL);
}

static bool	fmt_dispatch_click(t_gui *gui, t_vec2i m)
{
	int	bw;

	bw = (POPUP_W - POPUP_PAD * 3) / 2;
	if (phit(m, vec2i(gui->crud->pos.x + POPUP_PAD,
			gui->crud->pos.y + 36 + POPUP_PAD), vec2i(bw, POPUP_ITEM_H)))
	{
		gui->crud->mesh_fmt = MESH_FMT_OBJ;
		gui->crud->popup = POPUP_MESH_PATH;
		ft_memset(gui->crud->path_buf, 0, sizeof(gui->crud->path_buf));
		gui->crud->path_len = 0;
		return (true);
	}
	if (phit(m, vec2i(gui->crud->pos.x + POPUP_PAD * 2 + bw,
			gui->crud->pos.y + 36 + POPUP_PAD), vec2i(bw, POPUP_ITEM_H)))
	{
		gui->crud->mesh_fmt = MESH_FMT_GLB;
		gui->crud->popup = POPUP_MESH_PATH;
		ft_memset(gui->crud->path_buf, 0, sizeof(gui->crud->path_buf));
		gui->crud->path_len = 0;
		return (true);
	}
	return (false);
}

bool	click_popup_mesh_fmt(t_gui *gui, t_vec2i mouse)
{
	if (fmt_dispatch_click(gui, mouse))
		return (true);
	if (phit(mouse, vec2i(gui->crud->pos.x + POPUP_PAD,
		gui->crud->pos.y + gui->crud->h - 36), vec2i(80, 26)))
		gui->crud->popup = POPUP_SHAPE;
	else
		gui->crud->popup = POPUP_NONE;
	return (true);
}

