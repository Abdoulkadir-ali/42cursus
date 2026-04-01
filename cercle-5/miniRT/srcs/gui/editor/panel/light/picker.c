/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:40:00 by abdoali          ###   ########.fr       */
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
	p.y = 104;
	get_ambient_sliders(gui->scene, sl);
	i = -1;
	while (++i < 4)
	{
		if (try_islider_click(gui, mouse, p, sl[i], NULL))
			return (true);
		p.y += 30;
	}
	return (false);
}
