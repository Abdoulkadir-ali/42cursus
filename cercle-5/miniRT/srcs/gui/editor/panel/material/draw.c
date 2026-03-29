/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/29 10:03:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
void	draw_material_panel_text(t_gui *gui, int x)
{
	t_material	*mat;
	t_islider	sl[11];
	int			count;
	int			i;
	int			y;

	mat = get_selected_material(gui);
	if (!mat)
	{
		gui_draw_string(gui, "No material", x + 8, 90, COL_TEXT);
		return ;
	}
	gui_draw_string(gui, "MATERIAL", x + 8, 72, COL_HOVER);
	if (mat->name)
		gui_draw_string(gui, mat->name, x + 8, 88, COL_TEXT);
	else
		gui_draw_string(gui, "(unnamed)", x + 8, 88, COL_TEXT);
	build_mat_sliders(mat, sl, &count);
	y = 104;
	i = 0;
	while (i < count)
	{
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}
}

