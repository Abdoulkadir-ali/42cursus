/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_light_panel(t_gui *gui, t_vec2i pos)
{
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	char		*type;

	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return ;
	lt = &gui->scene->lights[gui->selection.index];
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, 88,
		COL_HOVER, "LIGHT");
	type = "Type: Point";
	if (lt->type == LIGHT_SPOT)
		type = "Type: Spot";
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, 100, COL_TEXT, type);
	build_light_sliders(lt, sl, &count);
	draw_panel_sliders(gui, sl, count, (t_vec2i){pos.x + 8, 116});
}
