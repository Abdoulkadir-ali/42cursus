/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 17:11:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	sync_group_materials(t_gui *gui)
{
	(void)gui;
}

static void	material_sync_invalidate(t_gui *gui)
{
	sync_group_materials(gui);
	rebuild_bvh(gui);
}

bool	material_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_material	*mat;
	t_islider	sl[11];
	int			count;
	int			i;
	int			y;
	int			x;

	mat = get_selected_material(gui);
	if (!mat)
		return (false);
	x = gui->win.disp_size.x - gui->inspector->box.size.x;
	build_mat_sliders(mat, sl, &count);
	y = 104;
	i = -1;
	while (++i < count)
	{
		if (try_islider_click(gui, mouse, (t_slider_arg){vec2i(x + 8, y),
				sl[i], material_sync_invalidate}))
			return (true);
		y += 30;
	}
	return (false);
}

