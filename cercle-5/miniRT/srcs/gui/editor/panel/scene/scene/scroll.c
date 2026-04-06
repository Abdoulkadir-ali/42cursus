/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	scene_panel_handle_scroll(t_gui *gui, int button)
{
	size_t	max_scroll;
	size_t	rows;

	if (!gui->scene_panel.visible || !gui->scene)
		return (false);
	if (gui->input.mouse.x >= gui->scene_panel.width)
		return (false);
	rows = count_scene_rows(gui->scene);
	max_scroll = rows * ROW_H;
	if (button == BUTTON_SCROLL_UP)
		gui->scene_panel.scroll -= ROW_H;
	else if (button == BUTTON_SCROLL_DOWN)
		gui->scene_panel.scroll += ROW_H;
	if (gui->scene_panel.scroll < 0)
		gui->scene_panel.scroll = 0;
	if (gui->scene_panel.scroll > max_scroll)
		gui->scene_panel.scroll = max_scroll;
	return (true);
}
