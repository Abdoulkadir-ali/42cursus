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

#include "editor.h"
/**
 * @brief Coordinates hit test for popup elements.
 */
bool	phit(t_vec2i m, t_gui_box box)
{
	return (m.x >= box.pos.x && m.x < box.pos.x + box.size.x
		&& m.y >= box.pos.y && m.y < box.pos.y + box.size.y);
}

/**
 * @brief Draws a centered modal background dimming the rest of the UI.
 */
void	draw_modal_bg(t_gui *gui)
{
	t_panel	p[2];

	p[0].box = (t_gui_box){vec2i(0, 0), gui->win.disp_size};
	p[0].bg = COL_POPUP_DIM;
	p[0].brd = COL_POPUP_DIM;
	draw_panel(gui, p[0]);
	p[1].box = gui->crud->box;
	p[1].bg = COL_POPUP_BG;
	p[1].brd = COL_ACCENT;
	draw_panel(gui, p[1]);
}

/**
 * @brief Draws an interactive button within the popup modal.
 */
void	draw_popup_btn(t_gui *gui, t_vec2i pos, t_vec2i size,
	const char *lbl, int bg)
{
	t_panel	btn;

	btn.box = (t_gui_box){pos, size};
	btn.bg = bg;
	btn.brd = COL_BORDER;
	draw_panel(gui, btn);
	gui_draw_string(gui, (char *)lbl, pos.x + 8, pos.y + size.y / 2, COL_TEXT);
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
