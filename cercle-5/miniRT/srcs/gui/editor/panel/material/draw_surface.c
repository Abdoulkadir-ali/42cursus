/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_mat_surface_ext(t_gui *gui, t_material *mat, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	sl = (t_islider){"Reflect", SL_REFL_MIN, SL_REFL_MAX,
		&mat->reflectivity, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"IOR", SL_IOR_MIN, SL_IOR_MAX,
		&mat->refract_index, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Shininess", SL_SHINE_MIN, SL_SHINE_MAX,
		&mat->shininess, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
}

void	draw_mat_surface(t_gui *gui, t_material *mat, t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl;

	d = gui->win.disp_size;
	draw_insp_header(gui, (t_vec2i){p->x, p->y}, "Surface");
	p->y += ui_sy(INSP_HDR_STEP, d);
	sl = (t_islider){"Roughness", SL_ROUGH_MIN, SL_ROUGH_MAX,
		&mat->roughness, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Metallic", SL_METAL_MIN, SL_METAL_MAX,
		&mat->metallic, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	sl = (t_islider){"Opacity", SL_OPAC_MIN, SL_OPAC_MAX,
		&mat->transparency, sync_group_materials};
	draw_insp_row(gui, (t_vec2i){p->x, p->y}, sl);
	p->y += ui_sy(INSP_ROW_STEP, d);
	draw_mat_surface_ext(gui, mat, p);
}
