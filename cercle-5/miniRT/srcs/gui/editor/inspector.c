/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 05:11:45 by abdoali          ###   ########.fr       */
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

static t_physics_body	*get_selected_physics(t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	if (gui->selection.type == TYPE_SPHERE
		&& gui->selection.index < sc->sphere_count)
		return (&sc->spheres[gui->selection.index].phys);
	if (gui->selection.type == TYPE_MESH
		&& gui->selection.index < sc->group_count)
		return (&sc->groups[gui->selection.index].phys);
	return (NULL);
}

static int	get_tabs(t_type type, t_inspect_tab tabs[3],
	const char *labels[3])
{
	if (type == TYPE_SPHERE)
	{
		tabs[0] = TAB_TRANSFORM; labels[0] = "Transform";
		tabs[1] = TAB_MATERIAL;  labels[1] = "Material";
		tabs[2] = TAB_PHYSICS;   labels[2] = "Physics";
		return (3);
	}
	if (type == TYPE_MESH)
	{
		tabs[0] = TAB_INFO;      labels[0] = "Info";
		tabs[1] = TAB_TRANSFORM; labels[1] = "Transform";
		tabs[2] = TAB_MATERIAL;  labels[2] = "Material";
		tabs[3] = TAB_PHYSICS;   labels[3] = "Physics";
		return (4);
	}
	if (type == TYPE_LIGHT)
	{
		tabs[0] = TAB_TRANSFORM; labels[0] = "Transform";
		tabs[1] = TAB_LIGHT;     labels[1] = "Light";
		return (2);
	}
	tabs[0] = TAB_TRANSFORM; labels[0] = "Transform";
	tabs[1] = TAB_MATERIAL;  labels[1] = "Material";
	return (2);
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
	t_inspect_tab	tabs[4];
	const char		*labels[4];
	int				n;
	int				step;
	int				i;

	n = get_tabs(gui->selection.type, tabs, labels);
	step = INSPECTOR_W / n;
	i = 0;
	while (i < n)
	{
		if (gui->inspector.tab == tabs[i])
			mlx_string_put(gui->win.mlx, gui->win.win,
				x + step * i + 8, 70, COL_ACCENT, (char *)labels[i]);
		else
			mlx_string_put(gui->win.mlx, gui->win.win,
				x + step * i + 8, 70, COL_TEXT, (char *)labels[i]);
		i++;
	}
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

static void	dispatch_panel_draw(t_gui *gui, int x)
{
	t_physics_body	*phys;

	if (gui->inspector.tab == TAB_TRANSFORM)
		draw_transform_panel(gui, x);
	else if (gui->inspector.tab == TAB_MATERIAL)
		draw_material_panel_text(gui, x);
	else if (gui->inspector.tab == TAB_PHYSICS)
	{
		phys = get_selected_physics(gui);
		if (phys)
			draw_physics_panel(gui, phys, x);
	}
	else if (gui->inspector.tab == TAB_LIGHT)
		draw_light_panel(gui, x);
	else if (gui->inspector.tab == TAB_INFO)
		draw_mesh_info_panel(gui, x);
}

void	draw_inspector_text(t_gui *gui)
{
	int	x;

	if (!gui->inspector.visible || !gui->selection.active || !gui->scene)
		return ;
	x = gui->win.disp_w - gui->inspector.width;
	draw_inspector_header(gui, x);
	draw_inspector_tabs(gui, x);
	dispatch_panel_draw(gui, x);
}

static void	dispatch_panel_click(t_gui *gui, t_vec2i mouse)
{
	t_physics_body	*phys;

	if (gui->inspector.tab == TAB_MATERIAL)
		material_panel_handle_click(gui, mouse);
	else if (gui->inspector.tab == TAB_TRANSFORM)
		transform_panel_handle_click(gui, mouse);
	else if (gui->inspector.tab == TAB_PHYSICS)
	{
		phys = get_selected_physics(gui);
		if (phys)
			physics_panel_handle_click(gui, mouse, phys);
	}
	else if (gui->inspector.tab == TAB_LIGHT)
		light_panel_handle_click(gui, mouse);
}

bool	inspector_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_inspect_tab	tabs[4];
	const char		*labels[4];
	int				n;
	int				step;
	int				x;

	if (!gui->inspector.visible || !gui->selection.active)
		return (false);
	x = gui->win.disp_w - gui->inspector.width;
	if (mouse.x < x || mouse.x >= gui->win.disp_w)
		return (false);
	n = get_tabs(gui->selection.type, tabs, labels);
	step = INSPECTOR_W / n;
	if (mouse.y >= 60 && mouse.y <= 84)
	{
		n = (mouse.x - x) / step;
		if (n >= 0 && n < get_tabs(gui->selection.type, tabs, labels))
			gui->inspector.tab = tabs[n];
		return (true);
	}
	dispatch_panel_click(gui, mouse);
	return (true);
}
