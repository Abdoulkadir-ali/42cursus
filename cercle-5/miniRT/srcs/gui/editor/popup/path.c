/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:20:27 by abdoali          ###   ########.ft       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	get_display_path(t_gui *gui, char display[64])
{
	if (gui->crud->path_len <= 40)
		snprintf(display, 64, "> %s_", gui->crud->path_buf);
	else
		snprintf(display, 64, "> ...%s_",
			gui->crud->path_buf + gui->crud->path_len - 37);
}

static void	draw_field_bg(t_gui *gui, int ox, int y)
{
	t_panel	f;

	ft_memset(&f, 0, sizeof(t_panel));
	f.x = ox + POPUP_PAD;
	f.y = y;
	f.w = POPUP_W - POPUP_PAD * 2;
	f.h = POPUP_ITEM_H;
	f.bg = COL_POPUP_DIM;
	f.brd = COL_BORDER;
	if (gui->crud->path_error)
		f.brd = COL_POPUP_ERR;
	f.pos = vec2i(f.x, f.y);
	f.size = vec2i(f.w, f.h);
	draw_panel(gui, f);
}

static void	draw_path_field(t_gui *gui, int ox, int oy)
{
	char	display[64];
	int		y;
	int		color;

	y = oy + 36 + POPUP_PAD + 24;
	draw_field_bg(gui, ox, y);
	get_display_path(gui, display);
	color = COL_TEXT;
	if (gui->crud->path_error)
		color = COL_POPUP_ERR_TEXT;
	mlx_string_put(gui->win.mlx, gui->win.win, ox + POPUP_PAD + 6,
		y + POPUP_ITEM_H / 2, color, display);
	if (gui->crud->path_error)
		mlx_string_put(gui->win.mlx, gui->win.win, ox + POPUP_PAD,
			y + POPUP_ITEM_H + 6, COL_POPUP_ERR, "File not found");
}

void	draw_popup_mesh_path(t_gui *gui)
{
	int	ox;
	int	oy;

	ox = gui->crud->pos.x;
	oy = gui->crud->pos.y;
	draw_modal_bg(gui);
	if (gui->crud->mesh_fmt == MESH_FMT_OBJ)

		mlx_string_put(gui->win.mlx, gui->win.win, ox + POPUP_PAD, oy + POPUP_PAD,
			COL_ACCENT, "Add Mesh \x2D Path (OBJ)");
	else
		mlx_string_put(gui->win.mlx, gui->win.win, ox + POPUP_PAD, oy + POPUP_PAD,
			COL_ACCENT, "Add Mesh \x2D Path (GLB)");
	draw_path_field(gui, ox, oy);
	draw_popup_btn(gui, vec2i(ox + POPUP_PAD, oy + gui->crud->h - 36),
		vec2i(80, 26), "\x21\x90 Back", COL_POPUP_BTN);
	draw_popup_btn(gui, vec2i(ox + (POPUP_W - 70) / 2, oy + gui->crud->h - 36),
		vec2i(70, 26), "Load", COL_POPUP_BTN_OK);
	draw_popup_btn(gui, vec2i(ox + POPUP_W - 90 - POPUP_PAD,
		oy + gui->crud->h - 36), vec2i(90, 26), "Cancel", COL_POPUP_BTN_CANCEL);
}

bool	click_popup_mesh_path(t_gui *gui, t_vec2i mouse)
{
	int	ox;
	int	oy;

	ox = gui->crud->pos.x;
	oy = gui->crud->pos.y;
	if (phit(mouse, vec2i(ox + POPUP_PAD, oy + gui->crud->h - 36), vec2i(80, 26)))
	{
		gui->crud->popup = POPUP_MESH_FMT;
		return (true);
	}
	if (phit(mouse, vec2i(ox + (POPUP_W - 70) / 2, oy + gui->crud->h - 36),
			vec2i(70, 26)))
	{
		popup_load_mesh(gui);
		return (true);
	}
	if (phit(mouse, vec2i(ox + POPUP_W - 90 - POPUP_PAD, oy + gui->crud->h - 36),
			vec2i(90, 26)))
		gui->crud->popup = POPUP_NONE;
	return (true);
}
