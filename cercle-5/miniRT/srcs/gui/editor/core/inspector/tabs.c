/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	get_tabs(t_type type, t_inspect_tab tabs[4], const char *labels[4])
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

void	draw_inspector_tabs(t_gui *gui, t_vec2i pos)
{
	t_inspect_tab	tabs[4];
	const char		*labels[4];
	int				n;
	int				step;
	int				i;
	int				color;

	n = get_tabs(gui->selection.type, tabs, labels);
	step = INSPECTOR_W / n;
	i = -1;
	while (++i < n)
	{
		color = COL_TEXT;
		if (gui->inspector.tab == tabs[i])
			color = COL_ACCENT;
		mlx_string_put(gui->win.mlx, gui->win.win, pos.x + step * i + 8, 70,
			color, (char *)labels[i]);
	}
}
