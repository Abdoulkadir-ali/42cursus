/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_physics_panel(t_gui *gui, t_physics_body *ph, t_vec2i pos)
{
	t_vec2s		d;
	t_islider	sl[3];
	t_vec2i		p;

	d = gui->win.disp_size;
	if (!ph)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			pos.x + ui_sx(8, d), ui_sy(90, d), COL_TEXT, "No physics body");
		return ;
	}
	p = (t_vec2i){pos.x, ui_sy(90, d)};
	draw_insp_header(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, "Info");
	p.y += ui_sy(INSP_HDR_STEP, d);
	draw_vec3_label(gui, p, "Velocity (m/s)", ph->velocity);
	p.y += ui_sy(30, d);
	draw_vec3_label(gui, p, "Angular vel", ph->angular_velocity);
	p.y += ui_sy(34, d);
	draw_insp_header(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, "Properties");
	p.y += ui_sy(INSP_HDR_STEP, d);
	get_phys_sliders(ph, sl);
	draw_panel_insp_rows(gui, sl, 3, (t_vec2i){p.x + ui_sx(8, d), p.y});
	p.y += ui_sy(3 * INSP_ROW_STEP, d);
	draw_insp_toggle_row(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, "Static",
		ph->is_static);
}
