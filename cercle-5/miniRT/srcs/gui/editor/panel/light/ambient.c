/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/29 09:13:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_ambient_panel(t_gui *gui, int x)
{
	t_islider	sl[4];
	int			i;
	int			y;

	gui_draw_string(gui, "AMBIENT LIGHT", x + 8, 88, COL_HOVER);
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
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}
}
