/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_emission.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_em_rgb(t_gui *gui, t_material *mat, t_vec2i *p, t_vec2s d)
{
	t_islider	sl;

	p->y += ui_sy(6, d);
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Emission");
	draw_insp_color_swatch(gui, vec2i(p->x + ui_sx(INSP_IN_OFF + INSP_IN_W
				- 18, d), p->y), mat->emission);
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"R", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.x, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"G", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.y, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"B", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.z, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
}

void	draw_mat_emission(t_gui *gui, t_material *mat, t_vec2i *p)
{
	const t_vec2s	d = gui->win.disp_size;
	t_islider		sl;

	draw_em_rgb(gui, mat, p, d);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Power", SL_EM_POWER_MIN, SL_EM_POWER_MAX,
		&mat->em_intensity, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Radius", SL_EM_RADIUS_MIN, SL_EM_RADIUS_MAX,
		&mat->em_radius, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
}
