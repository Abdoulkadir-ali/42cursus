/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:21:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	set_tab_base(t_inspect_tab *tabs, const char **labels)
{
	tabs[0] = TAB_TRANSFORM;
	labels[0] = "Transform";
	tabs[1] = TAB_MATERIAL;
	labels[1] = "Material";
	tabs[2] = TAB_PHYSICS;
	labels[2] = "Physics";
}

static int	set_prim_tabs(t_inspect_tab *tabs, const char **labels)
{
	set_tab_base(tabs, labels);
	tabs[3] = TAB_OBJECT;
	labels[3] = "Metadata";
	return (4);
}

/**
 * @brief Categorizes and sets the available tabs for the selected object type.
 * @param type The object type.
 * @param tabs Output array for the tab identifiers.
 * @param labels Output array for the UI labels.
 * @return int Number of active tabs.
 */
int	get_tabs(t_type type, t_inspect_tab tabs[4], const char *labels[4])
{
	if (type == TYPE_MESH)
	{
		tabs[0] = TAB_INFO;
		labels[0] = "Info";
		set_tab_base(tabs + 1, labels + 1);
		return (4);
	}
	if (type == TYPE_LIGHT)
	{
		tabs[0] = TAB_TRANSFORM;
		labels[0] = "Transform";
		tabs[1] = TAB_LIGHT;
		labels[1] = "Light";
		return (2);
	}
	if (type == TYPE_SPHERE || type == TYPE_TRI || type == TYPE_RECT
		|| type == TYPE_PYRAMID || type == TYPE_BOX || type == TYPE_CAPSULE
		|| type == TYPE_CYLINDER)
	{
		return (set_prim_tabs(tabs, labels));
	}
	return (set_prim_tabs(tabs, labels));
}
