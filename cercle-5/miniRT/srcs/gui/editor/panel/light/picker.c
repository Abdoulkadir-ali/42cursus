/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	ambient_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_islider	sl[4];
	t_vec2i		p;
	t_vec2s		d;
	int			i;

	if (!gui->scene)
		return (false);
	d = gui->win.disp_size;
	p.x = d.x - gui->inspector.width + ui_sx(8, d);
	p.y = ui_sy(90 + INSP_HDR_STEP, d);
	get_ambient_sliders(gui->scene, sl);
	i = 0;
	while (i < 4)
	{
		if (insp_row_click(gui, mouse, p, sl[i]))
			return (true);
		p.y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}
