/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:20:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static void	on_scale_change(t_gui *gui)
{
	size_t	s;

	s = (size_t)(gui->settings.render_scale + 0.5);
	if (s < 1)
		s = 1;
	if (s > 8)
		s = 8;
	gui->render.scale = s;
	gui->render.dirty = true;
}

static void	draw_window_stats(t_gui *gui, t_vec2i o, int *y)
{
	char	buf[64];

	snprintf(buf, sizeof(buf), "Res: %zu x %zu",
		(size_t)gui->win.disp_size.x, (size_t)gui->win.disp_size.y);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, *y, COL_TEXT, buf);
	*y += 20;
	snprintf(buf, sizeof(buf), "Render: %zu x %zu (%zux)",
		(size_t)gui->win.size.x, (size_t)gui->win.size.y, gui->render.scale);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, *y, 0x606070, buf);
	*y += 24;
}

void	draw_settings_window_tab(t_gui *gui, t_vec2i o)
{
	t_islider	sl;
	char		buf[64];
	int			y;

	y = o.y + 12;
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, y, COL_HOVER, "WIN");
	y += 24;
	draw_window_stats(gui, o, &y);
	sl = (t_islider){"Scale", 1.0, 8.0,
		&gui->settings.render_scale, on_scale_change};
	draw_settings_slider(gui, vec2i(o.x + 8, y), sl);
	y += 36;
	snprintf(buf, sizeof(buf), "GUI: %.0f RT: %.0f",
		gui->render.fps, gui->render.render_fps);
	mlx_string_put(gui->win.mlx, gui->win.win, o.x + 8, y, 0x606070, buf);
}

bool	click_settings_window_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_islider	sl;
	int			y;

	y = o.y + 12 + 24 + 20 + 24;
	sl = (t_islider){"Scale", 1.0, 8.0,
		&gui->settings.render_scale, on_scale_change};
	return (try_settings_slider_click(gui, mouse, vec2i(o.x + 8, y), sl));
}
