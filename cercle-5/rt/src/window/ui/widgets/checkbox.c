/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

int	ui_checkbox(t_app *app, const char *label, int *v)
{
	int		id;
	int		hover;
	int		changed;
	t_vec2i	pos;
	t_vec2i	box;
	t_vec2i	hit_size;
	t_vec2i	mouse;

	id = app->ui.next_id++;
	pos = (t_vec2i){app->ui.cursor_x, app->ui.cursor_y};
	box = (t_vec2i){14, 14};
	hit_size = (t_vec2i){app->ui.panel_w - UI_PAD * 2, box.y};
	mouse = (t_vec2i){app->ui.mx, app->ui.my};
	hover = pt_in(mouse, pos, hit_size);
	changed = 0;
	if (hover && app->ui.mouse_left && !app->ui.mouse_left_prev)
	{
		*v = !*v;
		changed = 1;
		app->ui.active_id = id;
	}
	gfx_fill_rect(app, pos.x, pos.y, box.x, box.y, app->ui.theme.bg2);
	gfx_rect_outline(app, pos.x, pos.y, box.x, box.y, app->ui.theme.border);
	if (*v)
		gfx_fill_rect(app, pos.x + 3, pos.y + 3, box.x - 6, box.y - 6,
			app->ui.theme.accent);
	gfx_text(app, pos.x + box.x + 6, pos.y, label, app->ui.theme.text);
	app->ui.cursor_y += box.y + 4;
	return (changed);
}
