/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
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
		mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 90, COL_TEXT,
			"No material");
		return ;
	}
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER,
		"MATERIAL");
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

