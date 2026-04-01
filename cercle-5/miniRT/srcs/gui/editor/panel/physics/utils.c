/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:55:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_vec3_label(t_gui *gui, t_vec2i pos, const char *label, t_vec3 v)
{
	char	buf[80];

	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f", v.x, v.y, v.z);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, pos.y, COL_HOVER,
		(char *)label);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, pos.y + 14, COL_TEXT,
		buf);
}

void	draw_bool_label(t_gui *gui, t_vec2i pos, const char *label, bool val)
{
	char	buf[32];
	char	*status;

	status = "NO";
	if (val)
		status = "YES";
	snprintf(buf, sizeof(buf), "%s [%s]", label, status);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, pos.y, COL_TEXT, buf);
}

void	get_phys_sliders(t_physics_body *phys, t_islider sl[3])
{
	sl[0] = (t_islider){"Mass (kg)", SL_MASS_MIN, SL_MASS_MAX, &phys->mass};
	sl[1] = (t_islider){"Elasticity", SL_ELAST_MIN, SL_ELAST_MAX,
		&phys->elasticity};
	sl[2] = (t_islider){"Friction", SL_FRIC_MIN, SL_FRIC_MAX, &phys->friction};
}
