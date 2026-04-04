/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:20:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static void	build_rt_radios(t_gui *gui, t_iradio r[3])
{
	r[0] = (t_iradio){"Adaptive Scale",
		&gui->render.opts.adaptive_scale, NULL};
	r[1] = (t_iradio){"Reprojection",
		&gui->render.opts.reprojection, NULL};
	r[2] = (t_iradio){"Temporal Blend",
		&gui->render.opts.temporal_blend, NULL};
}

void	draw_settings_raytracer_tab(t_gui *gui, t_vec2i o)
{
	t_iradio	r[3];
	int			y;
	int			i;

	y = o.y + 12;
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + 8, y, COL_HOVER, "RAYTRACER");
	y += 24;
	build_rt_radios(gui, r);
	i = 0;
	while (i < 3)
	{
		draw_radio_row(gui, vec2i(o.x, y), r[i], SETTINGS_W - 16);
		y += SETTINGS_ROW_H + 4;
		i++;
	}
}

bool	click_settings_raytracer_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_iradio	r[3];
	int			y;
	int			i;

	y = o.y + 12 + 24;
	build_rt_radios(gui, r);
	i = 0;
	while (i < 3)
	{
		if (try_radio_click(gui, mouse, vec2i(o.x, y), r[i], SETTINGS_W - 16))
			return (true);
		y += SETTINGS_ROW_H + 4;
		i++;
	}
	return (false);
}
