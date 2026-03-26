/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
static void	*get_tr_cb(t_type type, int i)
{
	if (type == TYPE_SPHERE && i == 6)
		return (sphere_scale_sync);
	if (type == TYPE_BOX && i >= 6)
		return (box_scale_sync);
	if (type == TYPE_CAPSULE && i >= 6)
		return (capsule_dims_sync);
	if (type == TYPE_MESH)
		return (mesh_transform_sync);
	return (NULL);
}

/**
 * @brief Handles mouse clicks on the transform panel.
 * @param gui Pointer to the GUI context.
 * @param mouse The click coordinates.
 * @return true if the click was handled.
 */
bool	transform_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_transform	*tr;
	t_islider	sl[9];
	int			n[4];

	tr = get_selected_transform(gui);
	if (!tr)
		return (false);
	build_tr_sliders(tr, gui->selection.type, sl, &n[0]);
	n[1] = gui->win.disp_w - gui->inspector.width;
	n[2] = TR_PANEL_START_Y;
	n[3] = 0;
	while (n[3] < n[0])
	{
		if (try_islider_click(gui, mouse, (t_slider_arg){vec2i(n[1] + INSPECTOR_PAD, n[2]),
				sl[n[3]], get_tr_cb(gui->selection.type, n[3])}))
			return (true);
		n[2] += TR_PANEL_STEP_Y;
		n[3]++;
	}
	return (false);
}

