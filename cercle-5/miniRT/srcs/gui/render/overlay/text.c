/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:43:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_ui_help(t_gui *gui, int *y)
{
	int	ox;

	ox = SCENE_PANEL_W + 16;
	gui_draw_string(gui, "miniRT", ox, *y, COL_ACCENT);
	*y += 24;
	gui_draw_string(gui, "WASD  Move   SPACE/SHIFT  Up/Down", ox, *y, COL_TEXT);
	*y += 20;
	gui_draw_string(gui, "LMB   Look   MMB          Zoom", ox, *y, COL_TEXT);
	*y += 20;
	gui_draw_string(gui, "+/-   Speed  N/P  Maps  X  Physics", ox, *y, COL_TEXT);
	*y += 20;
}

void	draw_ui_status(t_gui *gui, int *y)
{
	int		ox;
	int		color;
	char	buf[64];

	ox = SCENE_PANEL_W + 16;
	if (gui->physics_enabled)
	{
		color = 0x44FF44;
		snprintf(buf, sizeof(buf), "[ X ]  PHYSICS  ON");
	}
	else
	{
		color = 0xFF4444;
		snprintf(buf, sizeof(buf), "[   ]  PHYSICS  OFF");
	}
	gui_draw_string(gui, buf, ox, *y, color);
	*y += 20;
}

void	draw_ui_object(t_gui *gui)
{
	char	buf[128];

	if (!gui->scene || gui->scene->primitives.count == 0)
		return ;
	snprintf(buf, sizeof(buf), "Primitives: %zu", gui->scene->primitives.count);
	gui_draw_string(gui, buf, 350, 38, COL_ACCENT);
}
