/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Draws the background panel for the scene hierarchy.
 * @param gui Pointer to the GUI.
 */
void	draw_scene_panel_bg(t_gui *gui)
{
	t_panel	panel;
	int		w;
	int		h;

	if (!gui->scene_panel->visible)
		return ;
	w = gui->scene_panel->box.size.x;
	h = gui->win.disp_size.y;
	panel = (t_panel){.box = (t_gui_box){vec2i(0, 0), vec2i(w, h)},
		.bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, panel);
}
