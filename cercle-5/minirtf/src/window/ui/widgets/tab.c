/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	ui_tab(t_app *app, const char *label, int selected, int bw)
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
	size = (t_vec2i){bw, UI_LINE_H + 6};
	mouse = (t_vec2i){app->ui.mx, app->ui.my};
	hover = pt_in(mouse, pos, size);
	c = selected ? app->ui.theme.accent
		: (hover ? app->ui.theme.btn_hov : app->ui.theme.bg2);
	gfx_fill_rect(app, pos.x, pos.y, size.x, size.y, c);
	gfx_text(app, pos.x + (size.x - gfx_text_width(label)) / 2,
		pos.y + 4, label, app->ui.theme.text);
	clicked = (hover && app->ui.mouse_left && !app->ui.mouse_left_prev);
	if (clicked)
	{
		app->ui.active_id = id;
		app->ui.tab_clicked = 1;
	}
	app->ui.cursor_x += size.x + 2;
	return (clicked);
}
