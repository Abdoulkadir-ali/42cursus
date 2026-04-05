/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_crud_btn(t_gui *gui, t_panel btn)
{
	t_vec2i	d;

	d = gui->win.disp_size;
	draw_panel(gui, btn);
	if (btn.lbl && *btn.lbl)
		mlx_string_put(gui->win.mlx, gui->win.win,
			btn.pos.x + ui_sx(8, d), btn.pos.y + btn.size.y / 2 + ui_sy(4, d), COL_TEXT,
			(char *)btn.lbl);
}

/*
** Scene panel header: miniRT title, pos, rot, keybinds — top CRUD_PANEL_H px.
** Bottom toolbar: [+ Add]  [DEL]  — pinned to the bottom of the left panel.
*/

static void	draw_scene_header(t_gui *gui)
{
	t_vec2i				d;
	t_camera_controller	*c;
	char				buf[96];
	int					sw;

	d = gui->win.disp_size;
	sw = (int)gui->scene_panel.width;
	c = &gui->cam_ctrl;
	draw_crud_btn(gui, (t_panel){vec2i(0, ui_sy(CRUD_PANEL_H - 1, d)),
		vec2i(sw, 1), COL_BORDER, COL_BORDER, ""});
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(16, d), 0xE0A820, "miniRT");
	snprintf(buf, sizeof(buf), "POS  %.1f  %.1f  %.1f",
		c->transform.pos.x, c->transform.pos.y, c->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(36, d), 0xA0C8FF, buf);
	snprintf(buf, sizeof(buf), "ROT  %.0f  %.0f",
		c->transform.rotation.pitch * 57.29,
		c->transform.rotation.yaw * 57.29);
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(52, d), 0xA0C8FF, buf);
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(68, d), 0x606070,
		"WASD Move  SPC/SHF Up/Dn");
	mlx_string_put(gui->win.mlx, gui->win.win, ui_sx(8, d), ui_sy(82, d), 0x606070,
		"LMB Look  X Phys  N/P Map");
	if (gui->rt_engine.stats.rays_frame > 0)
	{
		snprintf(buf, sizeof(buf), "%.1f ms  %lluK rays",
			gui->rt_engine.stats.last_render_ms,
			(unsigned long long)(gui->rt_engine.stats.rays_frame / 1000));
		mlx_string_put(gui->win.mlx, gui->win.win,
			ui_sx(8, d), ui_sy(CRUD_PANEL_H - 14, d), 0x404050, buf);
	}
}

void	draw_crud_buttons(t_gui *gui)
{
	t_vec2i	d;
	int		sw;
	int		bh;
	int		aw;
	int		del_bg;
	int		add_bg;
	int		by;

	if (!gui->scene_panel.visible)
		return ;
	draw_scene_header(gui);
	d = gui->win.disp_size;
	sw = (int)gui->scene_panel.width;
	bh = ui_sy(CRUD_BTN_H, d);
	aw = ui_sx(CRUD_ADD_W, d);
	by = (int)d.y - ui_sy(CRUD_BTN_H + 26, d);
	add_bg = 0x22222E;
	if (gui->crud.popup != POPUP_NONE)
		add_bg = 0x2A2A3A;
	del_bg = 0x22222E;
	if (gui->selection.active)
		del_bg = 0x38161A;
	draw_crud_btn(gui, (t_panel){vec2i(0, by - ui_sy(6, d)),
		vec2i(sw, bh + ui_sy(12, d)), 0x12121C, 0x12121C, ""});
	draw_crud_btn(gui, (t_panel){vec2i(0, by - ui_sy(7, d)),
		vec2i(sw, 1), COL_BORDER, COL_BORDER, ""});
	draw_crud_btn(gui, (t_panel){vec2i(ui_sx(4, d), by), vec2i(aw, bh),
		add_bg, COL_ACCENT, "+ Add"});
	draw_crud_btn(gui, (t_panel){vec2i(aw + ui_sx(10, d), by),
		vec2i(sw - aw - ui_sx(16, d), bh),
		del_bg, COL_ACCENT, "DEL"});
}

static bool	btn_hit(t_vec2i m, t_vec2i pos, t_vec2i size)
{
	return (m.x >= pos.x && m.x < pos.x + size.x
		&& m.y >= pos.y && m.y < pos.y + size.y);
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_vec2i	d;
	int		sw;
	int		bh;
	int		aw;
	int		by;

	d = gui->win.disp_size;
	sw = (int)gui->scene_panel.width;
	bh = ui_sy(CRUD_BTN_H, d);
	aw = ui_sx(CRUD_ADD_W, d);
	if (!gui->scene || !gui->scene_panel.visible)
		return (false);
	if (mouse.x >= (size_t)sw)
		return (false);
	by = (int)d.y - ui_sy(CRUD_BTN_H + 26, d);
	if (mouse.y < (size_t)(by - ui_sy(7, d)))
		return (false);
	if (btn_hit(mouse, vec2i(ui_sx(4, d), by), vec2i(aw, bh)))
	{
		if (gui->crud.popup == POPUP_NONE)
			gui->crud.popup = POPUP_SHAPE;
		else
			gui->crud.popup = POPUP_NONE;
		gui->render.dirty = true;
		return (true);
	}
	if (btn_hit(mouse, vec2i(aw + ui_sx(10, d), by),
			vec2i(sw - aw - ui_sx(16, d), bh))
		&& gui->selection.active)
	{
		editor_delete_selected(gui);
		gui->render.dirty = true;
		return (true);
	}
	return (true);
}
