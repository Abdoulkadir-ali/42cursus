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

#include "gui.h"
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
        mlx_string_put(gui->win.mlx, gui->win.win,
            x + 8, 90, COL_TEXT, "No transform");
        return ;
    }
    if (gui->selection.type == TYPE_SPHERE)
        tr->scale.y = tr->scale.z = tr->scale.x;
    mlx_string_put(gui->win.mlx, gui->win.win,
        x + 8, 88, COL_HOVER, "TRANSFORM");
    build_tr_sliders(tr, gui->selection.type, sl, &count);
    y = 104;
    i = 0;
	while (i < count)
	{
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}
}

