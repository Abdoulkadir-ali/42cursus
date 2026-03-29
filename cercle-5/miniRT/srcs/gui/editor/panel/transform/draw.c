/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
void	draw_transform_panel(t_gui *gui, int x)
{
    t_transform	*tr;
    t_islider	sl[9];
    int			count;
    int			i;
    int			y;

    tr = get_selected_transform(gui);
    if (!tr)
    {
        gui_draw_string(gui, "No transform", x + 8, 90, COL_TEXT);
        return ;
    }
    if (gui->selection->type == TYPE_SPHERE)
        tr->scale.y = tr->scale.z = tr->scale.x;
    gui_draw_string(gui, "TRANSFORM", x + 8, 88, COL_HOVER);
    build_tr_sliders(tr, gui->selection->type, sl, &count);
    y = 104;
    i = 0;
	while (i < count)
	{
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}
}

