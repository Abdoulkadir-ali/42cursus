/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 16:37:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gui_style.h"

const char	*g_gui_style_names[GUI_STYLE_COUNT] = {
	"TRON BLUE",
	"TRON ORANGE",
	"MATRIX",
	"CYBERPUNK",
	"NEON GRID"
};

static t_gui_theme	get_tron_blue_theme(void)
{
	t_gui_theme	theme;

	theme.background = 0x000A0F;
	theme.border = 0x00FFFF;
	theme.text_primary = 0xFFFFFF;
	theme.text_secondary = 0x00DDFF;
	theme.accent = 0x00CCFF;
	theme.highlight = 0x00FFFF;
	return (theme);
}

static t_gui_theme	get_tron_orange_theme(void)
{
	t_gui_theme	theme;

	theme.background = 0x0F0A00;
	theme.border = 0xFFAA00;
	theme.text_primary = 0xFFFFFF;
	theme.text_secondary = 0xFFCC66;
	theme.accent = 0xFF8800;
	theme.highlight = 0xFFAA00;
	return (theme);
}

static t_gui_theme	get_matrix_theme(void)
{
	t_gui_theme	theme;

	theme.background = 0x001100;
	theme.border = 0x00FF00;
	theme.text_primary = 0xCCFFCC;
	theme.text_secondary = 0x00DD00;
	theme.accent = 0x00AA00;
	theme.highlight = 0x00FF00;
	return (theme);
}

static t_gui_theme	get_cyberpunk_theme(void)
{
	t_gui_theme	theme;

	theme.background = 0x1A0033;
	theme.border = 0xFF00FF;
	theme.text_primary = 0xFFCCFF;
	theme.text_secondary = 0xFF66FF;
	theme.accent = 0xDD00DD;
	theme.highlight = 0xFF00FF;
	return (theme);
}

static t_gui_theme	get_neon_grid_theme(void)
{
	t_gui_theme	theme;

	theme.background = 0x000A14;
	theme.border = 0x00FFFF;
	theme.text_primary = 0xFFFFFF;
	theme.text_secondary = 0xFFFF00;
	theme.accent = 0xFF00FF;
	theme.highlight = 0x00FFFF;
	return (theme);
}

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
