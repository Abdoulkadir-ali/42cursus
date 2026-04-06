/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	get_basic_tabs(t_type type, t_inspect_tab tabs[4],
	const char *labels[4])
{
	if (type == TYPE_SPHERE || type == TYPE_TRI || type == TYPE_RECT
		|| type == TYPE_PYRAMID || type == TYPE_BOX || type == TYPE_CAPSULE
		|| type == TYPE_CYLINDER)
	{
		tabs[0] = TAB_TRANSFORM;
		labels[0] = "Transform";
		tabs[1] = TAB_MATERIAL;
		labels[1] = "Material";
		tabs[2] = TAB_PHYSICS;
		labels[2] = "Physics";
		return (3);
	}
	if (type == TYPE_MESH)
	{
		tabs[0] = TAB_INFO;
		labels[0] = "Info";
		tabs[1] = TAB_TRANSFORM;
		labels[1] = "Transform";
		tabs[2] = TAB_MATERIAL;
		labels[2] = "Material";
		tabs[3] = TAB_PHYSICS;
		labels[3] = "Physics";
		return (4);
	}
	return (0);
}

int	get_tabs(t_type type, t_inspect_tab tabs[4], const char *labels[4])
{
	int	n;

	n = get_basic_tabs(type, tabs, labels);
	if (n > 0)
		return (n);
	tabs[0] = TAB_TRANSFORM;
	labels[0] = "Transform";
	tabs[1] = TAB_MATERIAL;
	labels[1] = "Material";
	if (type == TYPE_LIGHT)
	{
		tabs[1] = TAB_LIGHT;
		labels[1] = "Light";
	}
	return (2);
}

static void	draw_tab_label(t_gui *gui, t_vec2i pos, struct s_tab_draw d, int i)
{
	t_vec2s	winsz;
	int		color;
	int		tx;

	winsz = gui->win.disp_size;
	color = COL_TEXT;
	if (gui->inspector.tab == d.tabs[i])
		color = COL_ACCENT;
	tx = pos.x + d.step * i + ui_sx(8, winsz);
	mlx_string_put(gui->win.mlx, gui->win.win, tx, ui_sy(70, winsz), color,
		d.labels[i]);
}

void	draw_inspector_tabs(t_gui *gui, t_vec2i pos)
{
	t_inspect_tab		tabs[4];
	const char			*labels[4];
	struct s_tab_draw	d;
	int					n;
	int					i;

	n = get_tabs(gui->selection.type, tabs, labels);
	d = (struct s_tab_draw){tabs, labels, gui->inspector.width / n};
	i = 0;
	while (i < n)
	{
		draw_tab_label(gui, pos, d, i);
		i++;
	}
}
