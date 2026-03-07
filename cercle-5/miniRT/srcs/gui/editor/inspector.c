/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 21:44:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

const char	*type_name_str(t_type type)
{
	if (type == TYPE_SPHERE)
		return ("Sphere");
	if (type == TYPE_PLANE)
		return ("Plane");
	if (type == TYPE_CYLINDER)
		return ("Cylinder");
	if (type == TYPE_CONE)
		return ("Cone");
	if (type == TYPE_LIGHT)
		return ("Light");
	if (type == TYPE_MESH)
		return ("Mesh");
	return ("Object");
}

static void	draw_inspector_header(t_gui *gui, int x)
{
	char	buf[64];

	snprintf(buf, sizeof(buf), "%s  #%d",
		type_name_str(gui->selection.type), gui->selection.index);
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 50, COL_ACCENT, buf);
}

static void	draw_inspector_tabs(t_gui *gui, int x)
{
	int	col_t;
	int	col_m;

	col_t = COL_TEXT;
	col_m = COL_TEXT;
	if (gui->inspector.tab == TAB_TRANSFORM)
		col_t = COL_ACCENT;
	else
		col_m = COL_ACCENT;
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 8, 70, col_t, "[Transform]");
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + INSPECTOR_W / 2, 70, col_m, "[Material]");
}

void	draw_inspector_bg(t_gui *gui)
{
	t_panel	panel;
	int		x;
	int		w;
	int		h;

	if (!gui->inspector.visible || !gui->selection.active)
		return ;
	w = gui->inspector.width;
	h = gui->win.disp_h;
	x = gui->win.disp_w - w;
	panel = (t_panel){.x = x, .y = 0, .w = w, .h = h,
		.bg = COL_BG, .brd = COL_BORDER,
		.pos = vec2i(x, 0), .size = vec2i(w, h)};
	draw_panel(gui, panel);
}

void	draw_inspector_text(t_gui *gui)
{
	int	x;

	if (!gui->inspector.visible || !gui->selection.active || !gui->scene)
		return ;
	x = gui->win.disp_w - gui->inspector.width;
	draw_inspector_header(gui, x);
	draw_inspector_tabs(gui, x);
	if (gui->inspector.tab == TAB_TRANSFORM)
		draw_transform_panel(gui, x);
	else
		draw_material_panel_text(gui, x);
}

bool	inspector_handle_click(t_gui *gui, t_vec2i mouse)
{
	int	x;

	if (!gui->inspector.visible || !gui->selection.active)
		return (false);
	x = gui->win.disp_w - gui->inspector.width;
	if (mouse.x < x || mouse.x >= gui->win.disp_w)
		return (false);
	if (mouse.y >= 60 && mouse.y <= 84)
	{
		if (mouse.x < x + gui->inspector.width / 2)
			gui->inspector.tab = TAB_TRANSFORM;
		else
			gui->inspector.tab = TAB_MATERIAL;
		return (true);
	}
	if (gui->inspector.tab == TAB_MATERIAL)
		material_panel_handle_click(gui, mouse);
	else
		transform_panel_handle_click(gui, mouse);
	return (true);
}
