/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_panel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 05:10:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

void	editor_init(t_gui *gui)
{
	gui->scene_panel.visible = true;
	gui->scene_panel.width = SCENE_PANEL_W;
	gui->scene_panel.scroll = 0;
	gui->scene_panel.hovered_row = -1;
	gui->inspector.visible = false;
	gui->inspector.width = INSPECTOR_W;
	gui->inspector.tab = TAB_TRANSFORM;
	gui->selection.active = false;
	gui->selection.type = TYPE_NONE;
	gui->selection.index = -1;
}

static int	count_mesh_entries(t_scene *sc)
{
	return (sc->group_count);
}

static int	mesh_row_to_idx(t_scene *sc, int r)
{
	(void)sc;
	return (r);	/* r IS the group index */
}

static int	count_scene_rows(t_scene *sc)
{
	return (sc->light_count + sc->sphere_count + sc->plane_count
		+ sc->cylinder_count + sc->cone_count + count_mesh_entries(sc));
}

static int	row_strip(int *r, int count, t_type t, t_type *ty, int *idx)
{
	if (*r < count)
	{
		*ty = t;
		*idx = *r;
		return (1);
	}
	*r -= count;
	return (0);
}

static void	row_to_object(t_gui *gui, int r, t_type *ty, int *idx)
{
	t_scene	*sc;

	sc = gui->scene;
	*ty = TYPE_NONE;
	*idx = -1;
	if (row_strip(&r, sc->light_count, TYPE_LIGHT, ty, idx))
		return ;
	if (row_strip(&r, sc->sphere_count, TYPE_SPHERE, ty, idx))
		return ;
	if (row_strip(&r, sc->plane_count, TYPE_PLANE, ty, idx))
		return ;
	if (row_strip(&r, sc->cylinder_count, TYPE_CYLINDER, ty, idx))
		return ;
	if (row_strip(&r, sc->cone_count, TYPE_CONE, ty, idx))
		return ;
	if (r < count_mesh_entries(sc))
	{
		*ty = TYPE_MESH;
		*idx = mesh_row_to_idx(sc, r);
	}
}

static const char	*row_type_prefix(t_type type)
{
	if (type == TYPE_LIGHT)
		return ("[LT]");
	if (type == TYPE_SPHERE)
		return ("[SP]");
	if (type == TYPE_PLANE)
		return ("[PL]");
	if (type == TYPE_CYLINDER)
		return ("[CY]");
	if (type == TYPE_CONE)
		return ("[CO]");
	if (type == TYPE_MESH)
		return ("[ME]");
	return ("[??]");
}

static void	draw_one_row(t_gui *gui, int y_px, t_type ty, int idx)
{
	char	buf[64];
	int		col;

	col = COL_TEXT;
	if (gui->selection.active && gui->selection.type == ty
		&& gui->selection.index == idx)
		col = COL_SELECTED;
	if (ty == TYPE_MESH && idx >= 0
		&& idx < gui->scene->group_count
		&& gui->scene->groups[idx].name)
	{
		snprintf(buf, sizeof(buf), "[ME] %.55s",
			gui->scene->groups[idx].name);
	}
	else
		snprintf(buf, sizeof(buf), "%s %d", row_type_prefix(ty), idx);
	mlx_string_put(gui->win.mlx, gui->win.win, 12, y_px, col, buf);
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
	y_px = (CRUD_PANEL_H + 8) - gui->scene_panel.scroll;
	while (row < total && y_px < gui->win.disp_h - 8)
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

void	draw_scene_panel_bg(t_gui *gui)
{
	t_panel	panel;
	int		w;
	int		h;

	if (!gui->scene_panel.visible)
		return ;
	w = gui->scene_panel.width;
	h = gui->win.disp_h;
	panel = (t_panel){.x = 0, .y = 0, .w = w, .h = h,
		.bg = COL_BG, .brd = COL_BORDER,
		.pos = vec2i(0, 0), .size = vec2i(w, h)};
	draw_panel(gui, panel);
}

void	draw_scene_panel_text(t_gui *gui)
{
	char	buf[48];
	int		total;

	if (!gui->scene_panel.visible)
		return ;
	total = gui->scene ? count_scene_rows(gui->scene) : 0;
	snprintf(buf, sizeof(buf), "OBJECTS  %d", total);
	mlx_string_put(gui->win.mlx, gui->win.win, 8, CRUD_PANEL_H + 8, COL_ACCENT, buf);
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
