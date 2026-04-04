/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:20:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

static void	on_solver_change(t_gui *gui)
{
	size_t	v;

	v = (size_t)gui->settings.solver_iters;
	if (v < 1)
		v = 1;
	gui->phys_engine.settings.solver_iterations = v;
}

static void	build_phys_sliders(t_gui *gui, t_islider sl[3])
{
	sl[0] = (t_islider){"Time Scale", 0.0, 5.0,
		&gui->phys_engine.settings.time_scale, NULL};
	sl[1] = (t_islider){"Gravity Y", -50.0, 50.0,
		&gui->phys_engine.settings.gravity.y, NULL};
	sl[2] = (t_islider){"Solver Iterations", 1.0, 30.0,
		&gui->settings.solver_iters, on_solver_change};
}

void	draw_settings_physics_tab(t_gui *gui, t_vec2i o)
{
	t_iradio	r;
	t_islider	sl[3];
	int			y;
	int			i;

	y = o.y + 12;
	mlx_string_put(gui->win.mlx, gui->win.win,
		o.x + 8, y, COL_HOVER, "PHYSICS");
	y += 24;
	r = (t_iradio){"Enabled", &gui->physics_enabled, NULL};
	draw_radio_row(gui, vec2i(o.x, y), r, SETTINGS_W - 16);
	y += SETTINGS_ROW_H + 4;
	build_phys_sliders(gui, sl);
	i = 0;
	while (i < 3)
	{
		draw_slider_row(gui, vec2i(o.x + 8, y), sl[i]);
		y += SETTINGS_ROW_H + 4;
		i++;
	}
}

bool	click_settings_physics_tab(t_gui *gui, t_vec2i mouse, t_vec2i o)
{
	t_iradio	r;
	t_islider	sl[3];
	int			y;
	int			i;

	y = o.y + 12 + 24;
	r = (t_iradio){"Enabled", &gui->physics_enabled, NULL};
	if (try_radio_click(gui, mouse, vec2i(o.x, y), r, SETTINGS_W - 16))
		return (true);
	y += SETTINGS_ROW_H + 4;
	build_phys_sliders(gui, sl);
	i = 0;
	while (i < 3)
	{
		if (try_islider_click(gui, mouse, vec2i(o.x + 8, y), sl[i]))
			return (true);
		y += SETTINGS_ROW_H + 4;
		i++;
	}
	return (false);
}
