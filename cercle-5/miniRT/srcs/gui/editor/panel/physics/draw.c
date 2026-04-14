/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 04:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_phys_props(t_gui *gui, t_physics_body *ph, t_vec2i *p,
		t_vec2s d)
{
	t_islider	sl[3];

	draw_insp_header(gui, (t_vec2i){p->x + ui_sx(8, d), p->y}, "Info");
	p->y += ui_sy(INSP_HDR_STEP, d);
	draw_vec3_label(gui, *p, "Velocity (m/s)", ph->velocity);
	p->y += ui_sy(30, d);
	draw_vec3_label(gui, *p, "Angular vel", ph->angular_velocity);
	p->y += ui_sy(34, d);
	draw_insp_header(gui, (t_vec2i){p->x + ui_sx(8, d), p->y}, "Properties");
	p->y += ui_sy(INSP_HDR_STEP, d);
	get_phys_sliders(ph, sl);
	draw_panel_insp_rows(gui, sl, 3, (t_vec2i){p->x + ui_sx(8, d), p->y});
	p->y += ui_sy(3 * INSP_ROW_STEP, d);
	draw_insp_toggle_row(gui, (t_vec2i){p->x + ui_sx(8, d), p->y}, "Static",
		ph->is_static);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

static void	draw_mat_info(t_gui *gui, t_material *mat, t_vec2i p, t_vec2s d)
{
	t_islider	tsl;

	draw_insp_header(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, "Temperature");
	p.y += ui_sy(INSP_HDR_STEP, d);
	tsl = (t_islider){"Temp(K)", SL_TEMP_MIN, SL_TEMP_MAX,
		&mat->temperature, sync_temperature};
	draw_insp_row(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, tsl);
	p.y += ui_sy(INSP_ROW_STEP, d);
	tsl = (t_islider){"Power", SL_EM_POWER_MIN, SL_EM_POWER_MAX,
		&mat->em_intensity, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, tsl);
}

void	draw_physics_panel(t_gui *gui, t_physics_body *ph, t_vec2i pos)
{
	t_vec2s		d;
	t_material	*mat;
	t_vec2i		p;

	d = gui->win.disp_size;
	p = (t_vec2i){pos.x, ui_sy(90, d)};
	if (!ph)
		mlx_string_put_c(gui->win.mlx, gui->win.win,
			pos.x + ui_sx(8, d), ui_sy(90, d), COL_TEXT, "No physics body");
	else
		draw_phys_props(gui, ph, &p, d);
	mat = get_selected_material(gui);
	if (!mat)
		return ;
	p.y += ui_sy(6, d);
	draw_mat_info(gui, mat, p, d);
}
