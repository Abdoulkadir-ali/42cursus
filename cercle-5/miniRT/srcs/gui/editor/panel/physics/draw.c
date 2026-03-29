/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 14:55:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
void	draw_physics_panel(t_gui *gui, t_physics_body *phys, int x)
{
    t_islider	 sl[3];
    int		 i;
    int		 y;

    if (!phys)
    {
        gui_draw_string(gui, "No physics body", x + 8, 90, COL_TEXT);
        return ;
    }
    gui_draw_string(gui, "PHYSICS", x + 8, 88, COL_HOVER);
    y = 104;
    build_phys_sliders(phys, sl);
    i = 0;
	while (i < 3)
	{
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}

    draw_bool_label(gui, &(t_bool_label_arg){vec2i(x, y), "Static", phys->is_static});
}
