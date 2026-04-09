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

void	draw_slot_btn(t_gui *gui, t_panel btn, bool active);
void	draw_mat_surface(t_gui *gui, t_material *mat, t_vec2i *p);
void	draw_mat_albedo(t_gui *gui, t_material *mat, t_vec2i *p, int slot);
void	draw_mat_emission(t_gui *gui, t_material *mat, t_vec2i *p);

static void	draw_mat_slot_buttons(t_gui *gui, t_vec2i pos, int active,
		t_vec2s d)
{
	int				bw;
	int				bh;
	int				gap;
	const char		*lbl[4];

	lbl[0] = "Origin";
	lbl[1] = "Checker";
	lbl[2] = "Solid";
	lbl[3] = "Texture";
	bw = (ui_sx(gui->inspector.width - 18, d) - ui_sx(3, d)) / 2;
	bh = ui_sy(18, d);
	gap = ui_sx(3, d);
	draw_slot_btn(gui, (t_panel){pos, vec2s(bw, bh), 0, 0, lbl[0]},
		active == 0);
	draw_slot_btn(gui, (t_panel){vec2i(pos.x + bw + gap, pos.y),
		vec2s(bw, bh), 0, 0, lbl[1]}, active == 1);
	draw_slot_btn(gui, (t_panel){vec2i(pos.x, pos.y + bh + gap),
		vec2s(bw, bh), 0, 0, lbl[2]}, active == 2);
	draw_slot_btn(gui, (t_panel){vec2i(pos.x + bw + gap, pos.y + bh + gap),
		vec2s(bw, bh), 0, 0, lbl[3]}, active == 3);
}

static void	draw_fdf_mode_row(t_gui *gui, t_vec2i pos, t_vec2s d)
{
	t_mesh		*fdf;
	t_fdf_state	*state;
	int			bw;
	int			gap;
	t_fdf_mode	cur;

	fdf = get_selected_fdf_mesh(gui);
	if (!fdf)
		return ;
	state = (t_fdf_state *)fdf->extra;
	cur = FDF_MODE_HEIGHT;
	if (state)
		cur = state->mode;
	bw = (ui_sx(gui->inspector.width - 18, d) - ui_sx(3, d)) / 2;
	gap = ui_sx(3, d);
	draw_insp_header(gui, pos, "FDF Mode");
	pos.y += ui_sy(INSP_HDR_STEP, d);
	draw_slot_btn(gui, (t_panel){pos, vec2s(bw, ui_sy(18, d)), 0, 0,
		"Heightmap"}, cur == FDF_MODE_HEIGHT);
	draw_slot_btn(gui, (t_panel){vec2i(pos.x + bw + gap, pos.y),
		vec2s(bw, ui_sy(18, d)), 0, 0, "Picture"}, cur == FDF_MODE_PICTURE);
}

void	draw_material_panel_text(t_gui *gui, t_vec2i pos)
{
	t_material	*mat;
	t_vec2i		p;
	t_vec2s		d;
	int			slot;

	mat = get_selected_material(gui);
	d = gui->win.disp_size;
	p = (t_vec2i){pos.x + ui_sx(8, d), ui_sy(92, d)};
	slot = get_selected_group_slot(gui);
	if (gui->tex_popup_input)
		gui->tex_popup_input->visible = (slot == 3 && gui->selection.active);
	draw_mat_slot_buttons(gui, p, slot, d);
	p.y += ui_sy(44, d);
	draw_fdf_mode_row(gui, p, d);
	if (get_selected_fdf_mesh(gui))
		p.y += ui_sy(INSP_HDR_STEP + 26, d);
	if (!mat && slot == 3)
		gui_draw_string(gui, "No texture — click Texture to load",
			(t_vec2i){p.x, p.y}, COL_TEXT);
	if (!mat)
		return ;
	draw_mat_surface(gui, mat, &p);
	draw_mat_albedo(gui, mat, &p, slot);
	draw_mat_emission(gui, mat, &p);
}
