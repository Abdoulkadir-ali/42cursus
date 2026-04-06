/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:33:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_scene_panel_bg(t_gui *gui)
{
	t_panel	p;
	t_vec2s	s;

	if (!gui->scene_panel.visible)
		return ;
	s.x = gui->scene_panel.width;
	s.y = gui->win.disp_size.y;
	p = (t_panel){
		.pos = vec2i(0, 0), .size = s,
		.bg = COL_BG, .brd = COL_BORDER};
	draw_panel(gui, p);
}
