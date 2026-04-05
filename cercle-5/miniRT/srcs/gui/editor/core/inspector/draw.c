/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:14:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_inspector_header(t_gui *gui, t_vec2i pos)
{
	t_vec2i	d;
	char	buf[64];

	d = gui->win.disp_size;
	snprintf(buf, sizeof(buf), "%s  #%zu",
		type_name_str(gui->selection.type), gui->selection.index);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d), ui_sy(50, d), COL_ACCENT, buf);
}

void	draw_inspector_bg(t_gui *gui)
{
	t_panel	panel;
	t_vec2i	s;

	if (!gui->inspector.visible || !gui->selection.active)
		return ;
	s.x = gui->inspector.width;
	s.y = gui->win.disp_size.y;
	panel = (t_panel){
		.pos = vec2i(gui->win.disp_size.x - s.x, 0), .size = s,
		.bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, panel);
}

static void	dispatch_panel_draw(t_gui *gui, t_vec2i pos)
{
	t_physics_body	*phys;

	if (gui->inspector.tab == TAB_TRANSFORM)
		draw_transform_panel(gui, pos);
	else if (gui->inspector.tab == TAB_MATERIAL)
		draw_material_panel_text(gui, pos);
	else if (gui->inspector.tab == TAB_PHYSICS)
	{
		phys = get_selected_physics(gui);
		if (phys)
			draw_physics_panel(gui, phys, pos);
	}
	else if (gui->inspector.tab == TAB_LIGHT)
		draw_light_panel(gui, pos);
	else if (gui->inspector.tab == TAB_INFO)
		draw_mesh_info_panel(gui, pos);
}

void	draw_inspector_text(t_gui *gui)
{
	t_vec2i	p;

	if (!gui->inspector.visible || !gui->selection.active || !gui->scene)
		return ;
	p.x = gui->win.disp_size.x - gui->inspector.width;
	p.y = 0;
	draw_inspector_header(gui, p);
	draw_inspector_tabs(gui, p);
	dispatch_panel_draw(gui, p);
}
