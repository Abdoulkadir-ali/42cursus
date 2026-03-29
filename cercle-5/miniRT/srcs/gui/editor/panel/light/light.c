/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/29 09:12:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_light_panel(t_gui *gui, int x)
{
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	int			i;
	int			y;

	if (!gui->scene || (size_t)gui->selection->index >= gui->scene->light_count)
		return ;
	lt = &gui->scene->lights[gui->selection->index];
	gui_draw_string(gui, "LIGHT", x + 8, 88, COL_HOVER);
	if (lt->type == LIGHT_SPOT)
		gui_draw_string(gui, "Type: Spot", x + 8, 100, COL_TEXT);
	else
		gui_draw_string(gui, "Type: Point", x + 8, 100, COL_TEXT);
	build_light_sliders(lt, sl, &count);
	y = 116;
	i = 0;
	while (i < count)
	{
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}
}
