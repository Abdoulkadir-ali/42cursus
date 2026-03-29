/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 14:02:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_ui_help(t_gui *gui, int *y)
{
	int	ox;

	ox = SCENE_PANEL_W + 20;
	gui_draw_string(gui, "miniRT", ox, *y, COL_ACCENT);
	*y += 24;
	gui_draw_string(gui, "WASD Move  SPACE/SHIFT Up/Down  LMB Look",
		ox, *y, COL_TEXT_DIM);
	*y += 18;
}

void	draw_ui_status(t_gui *gui, int *y)
{
	int		ox;
	int		color;
	char	buf[64];

	ox = SCENE_PANEL_W + 20;
	if (gui->physics_enabled)
	{
		color = COL_SUCCESS;
		snprintf(buf, sizeof(buf), "Physics: ON");
	}
	else
	{
		color = COL_TEXT_DIM;
		snprintf(buf, sizeof(buf), "Physics: OFF");
	}
	gui_draw_string(gui, buf, ox, *y, color);
	*y += 20;
}

void	draw_ui_object(t_gui *gui)
{
	char	buf[128];

	if (!gui->scene || gui->scene->primitives.count == 0)
		return ;
	snprintf(buf, sizeof(buf), "Objects: %zu", gui->scene->primitives.count);
	gui_draw_string(gui, buf, 420, 38, COL_TEXT_DIM);
}
