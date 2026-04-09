/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:56:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_vec3_label(t_gui *gui, t_vec2i pos, char *label, t_vec3 v)
{
	t_vec2s	d;
	char	buf[80];

	d = gui->win.disp_size;
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f", v.x, v.y, v.z);
	mlx_string_put_c(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d), pos.y,
		COL_HOVER, label);
	mlx_string_put_c(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d),
		pos.y + ui_sy(14, d), COL_TEXT, buf);
}

void	draw_bool_label(t_gui *gui, t_vec2i pos, char *label, bool val)
{
	char	buf[32];
	char	*status;
	t_vec2s	d;

	d = gui->win.disp_size;
	status = "NO";
	if (val)
		status = "YES";
	snprintf(buf, sizeof(buf), "%s [%s]", label, status);
	mlx_string_put_c(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d), pos.y,
		COL_TEXT, buf);
}

void	get_phys_sliders(t_physics_body *ph, t_islider sl[3])
{
	sl[0] = (t_islider){"Mass (kg)", SL_MASS_MIN, SL_MASS_MAX, &ph->mass, 0};
	sl[1] = (t_islider){"Elasticity", SL_ELAST_MIN, SL_ELAST_MAX,
		&ph->elasticity, 0};
	sl[2] = (t_islider){"Friction", SL_FRIC_MIN, SL_FRIC_MAX, &ph->friction, 0};
}
