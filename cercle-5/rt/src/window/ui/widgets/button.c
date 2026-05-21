/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	ui_button_at(t_app *app, t_vec2i pos, t_vec2i size, const char *label)
{
	int				id;
	int				hover;
	int				clicked;
	unsigned int	c;
	t_vec2i			mouse;

	id = app->ui.next_id++;
	mouse = (t_vec2i){app->ui.mx, app->ui.my};
	hover = pt_in(mouse, pos, size);
	if (hover && app->ui.mouse_left && !app->ui.mouse_left_prev)
		app->ui.active_id = id;
	if (hover && app->input.mouse_left_clicked)
		app->ui.active_id = id;
	c = app->ui.theme.btn;
	if (hover)
		c = app->ui.theme.btn_hov;
	if (app->ui.active_id == id)
		c = app->ui.theme.btn_act;
	gfx_fill_rect(app, pos.x, pos.y, size.x, size.y, c);
	gfx_text(app, pos.x + (size.x - gfx_text_width(label)) / 2,
		pos.y + (size.y - 12) / 2, label, app->ui.theme.text);
	clicked = (hover && app->ui.active_id == id
			&& !app->ui.mouse_left && app->ui.mouse_left_prev);
	if (hover && app->input.mouse_left_clicked && app->ui.active_id == id)
		clicked = 1;
	return (clicked);
}

int	ui_button(t_app *app, const char *label)
{
	t_vec2i	pos;
	t_vec2i	size;
	int		clicked;

	pos = (t_vec2i){app->ui.cursor_x, app->ui.cursor_y};
	size = (t_vec2i){app->ui.panel_w - UI_PAD * 2, UI_LINE_H + 4};
	clicked = ui_button_at(app, pos, size, label);
	app->ui.cursor_y += size.y + 3;
	return (clicked);
}
