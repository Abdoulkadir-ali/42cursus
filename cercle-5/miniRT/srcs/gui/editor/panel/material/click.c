/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:33:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	material_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_material	*mat;
	t_islider	sl[11];
	int			count;
	int			i;
	t_vec2i		p;

	mat = get_selected_material(gui);
	if (!mat)
		return (false);
	p.x = gui->win.disp_size.x - gui->inspector.width;
	build_mat_sliders(mat, sl, &count);
	p.y = 104;
	i = -1;
	while (++i < count)
	{
		if (try_islider_click(gui, mouse, vec2i(p.x + 8, p.y), sl[i],
				sync_group_materials))
			return (true);
		p.y += 30;
	}
	return (false);
}
