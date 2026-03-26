/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
bool	light_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	int			i;
	int			y;
	int			x;

	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return (false);
	lt = &gui->scene->lights[gui->selection.index];
	x = gui->win.disp_w - gui->inspector.width;
	build_light_sliders(lt, sl, &count);
	y = 116;
	i = 0;
	while (i < count)
	{
		if (try_islider_click(gui, mouse, (t_slider_arg){vec2i(x + 8, y),
				sl[i], NULL}))
			return (true);
		y += 30;
		i++;
	}
	return (false);
}


bool	ambient_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
    t_islider	sl[4];
    int			i;
    int			y;
    int			x;

    if (!gui->scene)
        return (false);
    x = gui->win.disp_w - gui->inspector.width;
    sl[0] = (t_islider){"Intensity", SL_AMB_MIN, SL_AMB_MAX,
        &gui->scene->ambient.brightness};
    sl[1] = (t_islider){"Color R", SL_COL_MIN, SL_COL_MAX,
        &gui->scene->ambient.rgb.x};
    sl[2] = (t_islider){"Color G", SL_COL_MIN, SL_COL_MAX,
        &gui->scene->ambient.rgb.y};
    sl[3] = (t_islider){"Color B", SL_COL_MIN, SL_COL_MAX,
        &gui->scene->ambient.rgb.z};
    y = 104;
    i = 0;
    while (i < 4)
    {
        if (try_islider_click(gui, mouse, (t_slider_arg){vec2i(x + 8, y),
				sl[i], NULL}))
            return (true);
        y += 30;
        i++;
    }
    return (false);
}

