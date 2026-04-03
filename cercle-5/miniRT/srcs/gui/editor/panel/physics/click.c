/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:39:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	physics_panel_handle_click(t_gui *gui, t_vec2i mouse,
	t_physics_body *phys)
{
	t_islider	sl[3];
	int			i;
	t_vec2i		p;

	if (!phys)
		return (false);
	p.x = gui->win.disp_size.x - gui->inspector.width;
	p.y = 140;
	get_phys_sliders(phys, sl);
	i = 0;
	while (i < 3)
	{
		if (try_islider_click(gui, mouse, (t_vec2i){p.x + 8, p.y}, sl[i], NULL))
			return (true);
		p.y += 30;
		i++;
	}
	return (false);
}
