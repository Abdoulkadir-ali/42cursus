/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme.c                                            :+:      :+:    :+:     */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 19:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

static t_vec3	col_to_v3(unsigned int c)
{
	t_vec3	v;

	v.x = ((c >> 16) & 0xFF) / 255.0f;
	v.y = ((c >> 8) & 0xFF) / 255.0f;
	v.z = (c & 0xFF) / 255.0f;
	return (v);
}

static unsigned int	v3_to_col(t_vec3 v)
{
	return ((unsigned int)ft_argb(v.x, v.y, v.z) | 0xFF000000);
}

void	ui_set_theme(t_app *app, int preset)
{
	t_ui_theme	*t;

	t = &app->ui.theme;
	if (preset == 0)
	{
		t->bg = UI_COL_DEF_BG;
		t->bg2 = UI_COL_DEF_BG2;
		t->header = UI_COL_DEF_HEADER;
		t->border = UI_COL_DEF_BORDER;
		t->text = UI_COL_DEF_TEXT;
		t->text_dim = UI_COL_DEF_TEXT_D;
		t->btn = UI_COL_DEF_BTN;
		t->btn_hov = UI_COL_DEF_BTN_H;
		t->btn_act = UI_COL_DEF_BTN_A;
		t->accent = UI_COL_DEF_ACCENT;
	}
	else if (preset == 1)
	{
		t->bg = UI_COL_LIGHT_BG;
		t->bg2 = UI_COL_LIGHT_BG2;
		t->header = UI_COL_LIGHT_HEADER;
		t->border = UI_COL_LIGHT_BORDER;
		t->text = UI_COL_LIGHT_TEXT;
		t->text_dim = UI_COL_LIGHT_TEXT_D;
		t->btn = UI_COL_LIGHT_BTN;
		t->btn_hov = UI_COL_LIGHT_BTN_H;
		t->btn_act = UI_COL_LIGHT_BTN_A;
		t->accent = UI_COL_LIGHT_ACCENT;
	}
	else if (preset == 2)
	{
		t->bg = UI_COL_NEON_BG;
		t->bg2 = UI_COL_NEON_BG2;
		t->header = UI_COL_NEON_HEADER;
		t->border = UI_COL_NEON_BORDER;
		t->text = UI_COL_NEON_TEXT;
		t->text_dim = UI_COL_NEON_TEXT_D;
		t->btn = UI_COL_NEON_BTN;
		t->btn_hov = UI_COL_NEON_BTN_H;
		t->btn_act = UI_COL_NEON_BTN_A;
		t->accent = UI_COL_NEON_ACCENT;
	}
	else if (preset == 3)
	{
		t->bg = UI_COL_TRON_BG;
		t->bg2 = UI_COL_TRON_BG2;
		t->header = UI_COL_TRON_HEADER;
		t->border = UI_COL_TRON_BORDER;
		t->text = UI_COL_TRON_TEXT;
		t->text_dim = UI_COL_TRON_TEXT_D;
		t->btn = UI_COL_TRON_BTN;
		t->btn_hov = UI_COL_TRON_BTN_H;
		t->btn_act = UI_COL_TRON_BTN_A;
		t->accent = UI_COL_TRON_ACCENT;
	}
}

int	ui_color_swatch(t_app *app, const char *label, t_vec3 *v)
{
	t_vec2i	pos;
	t_vec2i	size;

	pos = (t_vec2i){app->ui.cursor_x, app->ui.cursor_y};
	size = (t_vec2i){30, 14};
	gfx_fill_rect(app, pos.x, pos.y, size.x, size.y, v3_to_col(*v));
	gfx_rect_outline(app, pos.x, pos.y, size.x, size.y, app->ui.theme.border);
	gfx_text(app, pos.x + size.x + 6, pos.y, label, app->ui.theme.text);
	app->ui.cursor_y += size.y + 4;
	return (0);
}

int	ui_color_swatch_hex(t_app *app, const char *label, unsigned int *col)
{
	t_vec3	v;
	int	changed;

	v = col_to_v3(*col);
	changed = 0;
	if (ui_color_swatch(app, label, &v))
	{
		*col = v3_to_col(v);
		changed = 1;
	}
	return (changed);
}
