/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
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
        mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 90, COL_TEXT,
            "No physics body");
        return ;
    }
    mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER, "PHYSICS");
    y = 104;
    draw_vec3_label(gui, &(t_vec3_label_arg){x, y, "Velocity (m/s)",
        phys->velocity});
    y += 32;
    draw_vec3_label(gui, &(t_vec3_label_arg){x, y, "Angular vel",
        phys->angular_velocity});
    y += 36;
    build_phys_sliders(phys, sl);
    i = 0;
	while (i < 3)
	{
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}

    draw_bool_label(gui, &(t_bool_label_arg){x, y, "Static", phys->is_static});
}
