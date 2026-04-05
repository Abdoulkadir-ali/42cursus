/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 11:15:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	ambient_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_islider	sl[4];
	t_vec2i		p;
	int			i;

	if (!gui->scene)
		return (false);
	p.x = gui->win.disp_size.x - gui->inspector.width + 8;
	p.y = 90 + INSP_HDR_STEP;
	get_ambient_sliders(gui->scene, sl);
	i = 0;
	while (i < 4)
	{
		if (insp_row_click(gui, mouse, p, sl[i]))
			return (true);
		p.y += INSP_ROW_STEP;
		i++;
	}
	return (false);
}

