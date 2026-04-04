/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:20:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static void	on_scale_change(t_gui *gui)
{
	size_t	s;

	s = (size_t)gui->settings.render_scale;
	if (s < 1)
		s = 1;
	if (s > 4)
		s = 4;
	gui->render.scale = s;
	gui->render.dirty = true;
}

void	draw_settings_window_tab(t_gui *gui, t_vec2i o)
{
	t_islider	sl;
	char		buf[64];
	int			y;

	y = o.y + 12;
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + 8, y, COL_HOVER, "WINDOW");
	y += 24;
	sl = (t_islider){"Render Scale", 1.0, 4.0,
		&gui->settings.render_scale, on_scale_change};
	draw_slider_row(gui, vec2i(o.x + 8, y), sl);
	y += 36;
	snprintf(buf, sizeof(buf), "active: %zu x    FPS: %.0f",
		gui->render.scale, gui->render.fps);
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + 8, y, 0x606070, buf);
}

bool	click_settings_window_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_islider	sl;
	int			y;

	y = o.y + 12 + 24;
	sl = (t_islider){"Render Scale", 1.0, 4.0,
		&gui->settings.render_scale, on_scale_change};
	return (try_islider_click(gui, mouse, vec2i(o.x + 8, y), sl));
}
