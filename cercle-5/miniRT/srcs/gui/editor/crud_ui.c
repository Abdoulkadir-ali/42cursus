/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 01:05:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

/*
** Toolbar row: [+ Add  v]  [  DEL  ]
** When crud.add_open: a 5-item dropdown opens above the toolbar.
*/

static void	draw_crud_btn(t_gui *gui, int x, int y, int w, int h,
	const char *lbl, int bg)
{
	t_panel	btn;

	btn = (t_panel){.x = x, .y = y, .w = w, .h = h,
		.bg = bg, .brd = COL_BORDER, .pos = vec2i(x, y), .size = vec2i(w, h)};
	draw_panel(gui, btn);
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 6, y + h / 2, COL_TEXT, (char *)lbl);
}

static void	draw_dropdown(t_gui *gui, int top_y)
{
	static const char	*labels[5] = {
		"  Sphere", "  Plane", "  Cylinder", "  Cone", "  Light"
	};
	int					i;
	int					y;
	t_panel				bg;

	bg = (t_panel){.x = 0, .y = top_y, .w = SCENE_PANEL_W,
		.h = 5 * CRUD_DROP_ITEM_H, .bg = 0x14141E, .brd = COL_BORDER,
		.pos = vec2i(0, top_y), .size = vec2i(SCENE_PANEL_W, 5 * CRUD_DROP_ITEM_H)};
	draw_panel(gui, bg);
	i = 0;
	y = top_y;
	while (i < 5)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			8, y + CRUD_DROP_ITEM_H / 2, COL_TEXT, (char *)labels[i]);
		y += CRUD_DROP_ITEM_H;
		i++;
	}
}

void	draw_crud_buttons(t_gui *gui)
{
	int	bar_y;
	int	del_bg;
	int	add_bg;
	int	drop_y;

	if (!gui->scene_panel.visible)
		return ;
	bar_y = gui->win.disp_h - CRUD_PANEL_H;
	del_bg = gui->selection.active ? 0x38161A : 0x22222E;
	add_bg = gui->crud.add_open ? 0x2A2A3A : 0x22222E;
	/* separator line */
	draw_crud_btn(gui, 0, bar_y, SCENE_PANEL_W, 1, "", COL_BORDER);
	bar_y += 4;
	/* [+ Add  v] button */
	draw_crud_btn(gui, 2, bar_y, CRUD_ADD_W, CRUD_BTN_H,
		"+ Add  v", add_bg);
	/* [DEL] button */
	draw_crud_btn(gui, CRUD_ADD_W + 6, bar_y,
		SCENE_PANEL_W - CRUD_ADD_W - 10, CRUD_BTN_H, "DEL", del_bg);
	/* dropdown items, drawn ABOVE the toolbar */
	if (gui->crud.add_open)
	{
		drop_y = bar_y - 5 * CRUD_DROP_ITEM_H;
		draw_dropdown(gui, drop_y);
	}
}

static bool	btn_hit(t_vec2i m, int x, int y, int w, int h)
{
	return (m.x >= x && m.x < x + w && m.y >= y && m.y < y + h);
}

static bool	dropdown_click(t_gui *gui, t_vec2i mouse, int drop_y)
{
	int	i;
	int	y;

	i = 0;
	y = drop_y;
	while (i < 5)
	{
		if (btn_hit(mouse, 0, y, SCENE_PANEL_W, CRUD_DROP_ITEM_H))
		{
			if (i == 0)
				editor_add_sphere(gui);
			else if (i == 1)
				editor_add_plane(gui);
			else if (i == 2)
				editor_add_cylinder(gui);
			else if (i == 3)
				editor_add_cone(gui);
			else
				editor_add_light(gui);
			gui->crud.add_open = false;
			return (true);
		}
		y += CRUD_DROP_ITEM_H;
		i++;
	}
	return (false);
}

bool	crud_handle_click(t_gui *gui, t_vec2i mouse)
{
	int	bar_y;
	int	btn_y;
	int	drop_y;

	if (!gui->scene || !gui->scene_panel.visible)
		return (false);
	bar_y = gui->win.disp_h - CRUD_PANEL_H;
	btn_y = bar_y + 5;
	drop_y = btn_y - 5 * CRUD_DROP_ITEM_H;
	/* dropdown items intercept clicks first */
	if (gui->crud.add_open && mouse.y >= drop_y
		&& mouse.y < btn_y)
		return (dropdown_click(gui, mouse, drop_y));
	/* [+ Add v] button */
	if (btn_hit(mouse, 2, btn_y, CRUD_ADD_W, CRUD_BTN_H))
	{
		gui->crud.add_open = !gui->crud.add_open;
		return (true);
	}
	/* [DEL] button */
	if (btn_hit(mouse, CRUD_ADD_W + 6, btn_y,
			SCENE_PANEL_W - CRUD_ADD_W - 10, CRUD_BTN_H)
		&& gui->selection.active)
	{
		gui->crud.add_open = false;
		editor_delete_selected(gui);
		return (true);
	}
	/* any click outside dropdown closes it */
	gui->crud.add_open = false;
	return (false);
}

