/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 23:49:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	draw_vec3_label(t_gui *gui, int x, int y,
	const char *label, t_vec3 v)
{
	char	buf[80];

	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f", v.x, v.y, v.z);
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, y, COL_HOVER, (char *)label);
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, y + 14, COL_TEXT, buf);
}

static void	draw_bool_label(t_gui *gui, int x, int y,
	const char *label, bool val)
{
	char	buf[32];

	snprintf(buf, sizeof(buf), "%s [%s]", label, val ? "YES" : "NO");
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, y, COL_TEXT, buf);
}

void	draw_physics_panel(t_gui *gui, t_physics_body *phys, int x)
{
	t_islider	sl[3];
	int			i;
	int			y;

	if (!phys)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			x + 8, 90, COL_TEXT, "No physics body");
		return ;
	}
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER, "PHYSICS");
	y = 104;
	draw_vec3_label(gui, x, y, "Velocity (m/s)", phys->velocity);
	y += 32;
	draw_vec3_label(gui, x, y, "Angular vel", phys->angular_velocity);
	y += 36;
	sl[0] = (t_islider){"Mass (kg)", SL_MASS_MIN, SL_MASS_MAX, &phys->mass};
	sl[1] = (t_islider){"Elasticity", SL_ELAST_MIN, SL_ELAST_MAX, &phys->elasticity};
	sl[2] = (t_islider){"Friction", SL_FRIC_MIN, SL_FRIC_MAX, &phys->friction};
	i = 0;
	while (i < 3)
	{
		draw_slider_row(gui, vec2i(x + 8, y), sl[i]);
		y += 30;
		i++;
	}
	draw_bool_label(gui, x, y, "Static", phys->is_static);
}

bool	physics_panel_handle_click(t_gui *gui, t_vec2i mouse,
	t_physics_body *phys)
{
	t_islider	sl[3];
	int			i;
	int			y;
	int			x;

	if (!phys)
		return (false);
	x = gui->win.disp_w - gui->inspector.width;
	y = 140;
	sl[0] = (t_islider){"Mass (kg)", SL_MASS_MIN, SL_MASS_MAX, &phys->mass};
	sl[1] = (t_islider){"Elasticity", SL_ELAST_MIN, SL_ELAST_MAX, &phys->elasticity};
	sl[2] = (t_islider){"Friction", SL_FRIC_MIN, SL_FRIC_MAX, &phys->friction};
	i = 0;
	while (i < 3)
	{
		if (try_islider_click(gui, mouse, vec2i(x + 8, y), sl[i]))
			return (true);
		y += 30;
		i++;
	}
	return (false);
}
