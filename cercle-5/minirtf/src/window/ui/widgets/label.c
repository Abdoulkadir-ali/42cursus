/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	ui_label(t_app *app, const char *s)
{
	t_vec2i	cursor;

	cursor = (t_vec2i){app->ui.cursor_x, app->ui.cursor_y};
	gfx_text(app, cursor.x, cursor.y, s, app->ui.theme.text);
	app->ui.cursor_y += UI_LINE_H;
}

void	ui_section(t_app *app, const char *s)
{
	app->ui.cursor_y += 4;
	gfx_text(app, app->ui.cursor_x, app->ui.cursor_y, s, app->ui.theme.text_dim);
	app->ui.cursor_y += UI_LINE_H + 2;
}

void	ui_label_value(t_app *app, const char *k, const char *v)
{
	t_vec2i	cursor;

	cursor = (t_vec2i){app->ui.cursor_x, app->ui.cursor_y};
	gfx_text(app, cursor.x, cursor.y, k, app->ui.theme.text_dim);
	gfx_text(app, cursor.x + 80, cursor.y, v, app->ui.theme.text);
	app->ui.cursor_y += UI_LINE_H;
}
