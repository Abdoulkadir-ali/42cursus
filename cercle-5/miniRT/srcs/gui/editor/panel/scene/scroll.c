/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/**
 * @brief Handles scroll events in the hierarchy panel.
 * @param gui Pointer to the GUI context.
 * @param button Mouse button index (scroll up/down).
 * @return true if handled.
 */
bool	scene_panel_handle_scroll(t_gui *gui, int button)
{
	int	max_scroll;
	int	rows;

	if (!gui->scene_panel->visible || !gui->scene)
		return (false);
	if (gui->input.mouse_x < 0 || gui->input.mouse_x >= gui->scene_panel->width)
		return (false);
	rows = count_scene_rows(gui->scene);
	max_scroll = rows * ROW_H;
	if (button == Button4)
		gui->scene_panel->scroll -= ROW_H;
	else if (button == Button5)
		gui->scene_panel->scroll += ROW_H;
	if (gui->scene_panel->scroll < 0)
		gui->scene_panel->scroll = 0;
	if (gui->scene_panel->scroll > max_scroll)
		gui->scene_panel->scroll = max_scroll;
	return (true);
}
