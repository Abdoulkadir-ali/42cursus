/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 17:22:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
bool	light_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	int			i;
	int			y;
	int			x;

	if (!gui->scene || (size_t)gui->selection->index >= gui->scene->light_count)
		return (false);
	lt = &gui->scene->lights[gui->selection->index];
	x = gui->win.disp_size.x - gui->inspector->box.size.x;
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
    x = gui->win.disp_size.x - gui->inspector->box.size.x;
	i = 0;
	while (g_props_ambient[i])
	{
		sl[i] = (t_islider){g_props_ambient[i]->name, g_props_ambient[i]->min,
			g_props_ambient[i]->max, NULL, g_props_ambient[i]};
		i++;
	}
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

