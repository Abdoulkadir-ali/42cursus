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

void	draw_scene_panel_text(t_gui *gui)
{
	char	buf[48];
	int		total;

	if (!gui->scene_panel.visible)
		return ;
	total = 0;
	if (gui->scene)
		total = count_scene_rows(gui->scene);
	snprintf(buf, sizeof(buf), "OBJECTS  %d", total);
	mlx_string_put(gui->win.mlx, gui->win.win, 8,
		CRUD_PANEL_H + 8, COL_ACCENT, buf);
	if (!gui->scene || total == 0)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			16, CRUD_PANEL_H + 24, 0x505060, "(empty)");
		draw_crud_buttons(gui);
		return ;
	}
	draw_scene_rows(gui);
	draw_crud_buttons(gui);
}
