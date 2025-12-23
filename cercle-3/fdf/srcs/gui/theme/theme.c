/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 16:27:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_gui_theme	get_tron_blue_theme(void)
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

t_gui_theme	get_tron_orange_theme(void)
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

t_gui_theme	get_matrix_theme(void)
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

t_gui_theme	get_cyberpunk_theme(void)
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

t_gui_theme	get_neon_grid_theme(void)
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
