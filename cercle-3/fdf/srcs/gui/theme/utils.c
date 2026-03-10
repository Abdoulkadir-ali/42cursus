/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:51:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Resolve the active GUI palette from the selected style enum.
 * @param style GUI style identifier.
 * @return Matching GUI theme palette.
 */
t_gui_theme	get_gui_theme(t_gui_style style)
{
	if (style == GUI_STYLE_TRON_BLUE)
		return (get_tron_blue_theme());
	else if (style == GUI_STYLE_TRON_ORANGE)
		return (get_tron_orange_theme());
	else if (style == GUI_STYLE_MATRIX)
		return (get_matrix_theme());
	else if (style == GUI_STYLE_CYBERPUNK)
		return (get_cyberpunk_theme());
	else if (style == GUI_STYLE_NEON_GRID)
		return (get_neon_grid_theme());
	return (get_tron_blue_theme());
}

/**
 * @brief Advance to the next GUI style and mirror it into the camera state.
 * @param gui GUI object whose style should be updated.
 */
void	cycle_gui_style(t_gui *gui)
{
	gui->gui_style = (gui->gui_style + 1) % GUI_STYLE_COUNT;
	gui->camera->gui_style = gui->gui_style;
}
