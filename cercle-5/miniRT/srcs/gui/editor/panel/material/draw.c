/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:33:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_material_panel_text(t_gui *gui, t_vec2i pos)
{
	t_material	*mat;
	t_islider	sl[11];
	int			count;
	int			i;
	int			y;

	mat = get_selected_material(gui);
	if (!mat)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			pos.x + 8, 90, COL_TEXT, "No material");
		return ;
	}
	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x + 8, 88, COL_HOVER, "MATERIAL");
	build_mat_sliders(mat, sl, &count);
	y = 104;
	i = -1;
	while (++i < count)
	{
		draw_slider_row(gui, vec2i(pos.x + 8, y), sl[i]);
		y += 30;
	}
}
