/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 17:22:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
bool	physics_panel_handle_click(t_gui *gui, t_vec2i mouse,
    t_physics_body *phys)
{
    t_islider	 sl[3];
    int		 i;
    int		 y;
    int		 x;

    if (!phys)
        return (false);
    x = gui->win.disp_size.x - gui->inspector->box.size.x;
    y = 140;
	i = 0;
	while (g_props_physics[i])
	{
		sl[i] = (t_islider){g_props_physics[i]->name, g_props_physics[i]->min,
			g_props_physics[i]->max, NULL, g_props_physics[i]};
		i++;
	}
    i = 0;
	while (i < 3)
	{
		if (try_islider_click(gui, mouse, (t_slider_arg){vec2i(x + 8, y),
				sl[i], NULL}))
			return (true);
		y += 30;
		i++;
	}
	return (false);
}

