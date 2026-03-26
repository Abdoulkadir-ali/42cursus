/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
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
    x = gui->win.disp_w - gui->inspector->width;
    y = 140;
    sl[0] = (t_islider){"Mass (kg)", SL_MASS_MIN, SL_MASS_MAX, &phys->mass};
    sl[1] = (t_islider){"Elasticity", SL_ELAST_MIN, SL_ELAST_MAX,
        &phys->elasticity};
    sl[2] = (t_islider){"Friction", SL_FRIC_MIN, SL_FRIC_MAX, &phys->friction};
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

