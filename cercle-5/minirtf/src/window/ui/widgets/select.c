/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	ui_select_row(t_app *app, const char *label, int selected)
{
	int				id;
	int				hover;
	int				clicked;
	unsigned int	c;
	t_vec2i			pos;
	t_vec2i			size;
	t_vec2i			mouse;

	id = app->ui.next_id++;
	pos = (t_vec2i){app->ui.cursor_x, app->ui.cursor_y};
	size = (t_vec2i){app->ui.panel_w - UI_PAD * 2, UI_LINE_H + 2};
	mouse = (t_vec2i){app->ui.mx, app->ui.my};
	hover = pt_in(mouse, pos, size);
	c = app->ui.theme.bg2;
	if (selected)
		c = app->ui.theme.btn_act;
	else if (hover)
		c = app->ui.theme.btn_hov;
	gfx_fill_rect(app, pos.x, pos.y, size.x, size.y, c);
	gfx_text(app, pos.x + 4, pos.y + 2, label, app->ui.theme.text);
	clicked = (hover && app->ui.mouse_left && !app->ui.mouse_left_prev);
	if (clicked)
		app->ui.active_id = id;
	app->ui.cursor_y += size.y + 1;
	return (clicked);
}
