/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:26:38 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:33:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "data.h"


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

int	get_gui_background_color(t_gui_style style)
{
	return (get_gui_theme(style).background);
}

int	get_gui_accent_color(t_gui_style style)
{
	return (get_gui_theme(style).accent);
}

int	get_gui_border_color(t_gui_style style)
{
	return (get_gui_theme(style).border);
}

int	get_gui_text_color(t_gui_style style)
{
	return (get_gui_theme(style).text_primary);
}

void	cycle_gui_style(t_data *data)
{
	data->camera.gui_style = (data->camera.gui_style + 1) % GUI_STYLE_COUNT;
}