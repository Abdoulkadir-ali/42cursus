/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:17:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

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

void	cycle_gui_style(t_gui *gui)
{
	gui->gui_style = (gui->gui_style + 1) % GUI_STYLE_COUNT;
	gui->camera->gui_style = gui->gui_style;
}
