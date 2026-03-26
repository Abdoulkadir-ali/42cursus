/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
/**
 * @brief Coordinates hit test for popup elements.
 */
bool	phit(t_vec2i m, t_vec2i pos, t_vec2i size)
{
	return (m.x >= pos.x && m.x < pos.x + size.x && m.y >= pos.y
		&& m.y < pos.y + size.y);
}

/**
 * @brief Draws a centered modal background dimming the rest of the UI.
 */
void	draw_modal_bg(t_gui *gui)
{
	t_panel	p[2];

	p[0] = (t_panel){.x = 0, .y = 0, .w = gui->win.disp_w, .h = gui->win.disp_h,
		.bg = COL_POPUP_DIM, .brd = COL_POPUP_DIM,
		.pos = vec2i(0, 0), .size = vec2i(gui->win.disp_w, gui->win.disp_h)};
	draw_panel(gui, p[0]);
	p[1] = (t_panel){.x = gui->crud.pos.x, .y = gui->crud.pos.y,
		.w = gui->crud.w, .h = gui->crud.h,
		.bg = COL_POPUP_BG, .brd = COL_ACCENT,
		.pos = gui->crud.pos, .size = vec2i(gui->crud.w, gui->crud.h)};
	draw_panel(gui, p[1]);
}


/**
 * @brief Draws an interactive button within the popup modal.
 */
void	draw_popup_btn(t_gui *gui, t_vec2i pos, t_vec2i size,
	const char *lbl, int bg)
{
	t_panel	btn;

	btn = (t_panel){.x = pos.x, .y = pos.y, .w = size.x, .h = size.y,
		.bg = bg, .brd = COL_BORDER,
		.pos = vec2i(pos.x, pos.y), .size = vec2i(size.x, size.y)};
	draw_panel(gui, btn);
	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x + 8, pos.y + size.y / 2, COL_TEXT, (char *)lbl);
}

/**
 * @brief Maps keysyms to shifted chars for path entry.
 */
char	popup_shift_char(int keycode)
{
	if (keycode >= 'a' && keycode <= 'z')
		return ((char)(keycode - 32));
	if (keycode == ':')
		return ('/');
	if (keycode == ';')
		return ('.');
	if (keycode == '.')
		return ('>');
	if (keycode == ',')
		return ('<');
	if (keycode == '-')
		return ('_');
	if (keycode >= '0' && keycode <= '9')
		return (")!@#$%^&*("[keycode - '0']);
	return ((char)keycode);
}
