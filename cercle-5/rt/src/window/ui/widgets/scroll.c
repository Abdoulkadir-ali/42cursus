/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	ui_scroll_begin(t_app *app, int h, int *scroll_y)
{
	t_vec2i	panel_pos;
	t_vec2i	panel_size;
	t_vec2i	mouse;

	app->ui.scissor_y0 = app->ui.cursor_y;
	app->ui.scissor_y1 = app->ui.cursor_y + h;
	panel_pos = (t_vec2i){app->ui.panel_x, app->ui.scissor_y0};
	panel_size = (t_vec2i){app->ui.panel_w, h};
	mouse = (t_vec2i){app->ui.mx, app->ui.my};
	if (pt_in(mouse, panel_pos, panel_size))
	{
		*scroll_y += app->input.mouse_wheel * 20;
		app->ui.consume_input = 1;
	}
	app->ui.scroll_y = *scroll_y;
	app->ui.cursor_y -= *scroll_y;
}

void	ui_scroll_end(t_app *app, int *scroll_y)
{
	int	content_h;
	int	view_h;

	content_h = (app->ui.cursor_y + app->ui.scroll_y) - app->ui.scissor_y0;
	view_h = app->ui.scissor_y1 - app->ui.scissor_y0;
	if (content_h < view_h)
		*scroll_y = 0;
	else if (*scroll_y < 0)
		*scroll_y = 0;
	else if (*scroll_y > content_h - view_h)
		*scroll_y = content_h - view_h;
	app->ui.cursor_y = app->ui.scissor_y1 + UI_PAD;
	app->ui.scissor_y0 = 0;
	app->ui.scissor_y1 = 0;
	app->ui.scroll_y = 0;
}
