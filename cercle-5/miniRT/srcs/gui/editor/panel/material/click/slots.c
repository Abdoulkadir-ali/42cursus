/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:10:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	ensure_slot_mat(t_gui *gui, int slot)
{
	t_index		id;
	t_material	*mat;

	if (!gui->scene || slot == 0)
		return ;
	if (slot_get_mat(gui, slot) != 0)
		return ;
	id = scene_add_fresh_material(gui->scene, vec3(255, 255, 255));
	if (id.error)
		return ;
	mat = &gui->scene->materials[id.i];
	if (slot == 1)
	{
		mat->albedo_map.type = TEX_CHECKER;
		mat->albedo_map.color_b = vec3(0, 0, 0);
		mat->albedo_map.scale = 4.0;
	}
	slot_set_mat(gui, slot, id.i);
}

bool	mat_hit_btn(t_gui *gui, t_vec2i mouse, t_vec2i pos, t_vec2s size)
{
	(void)gui;
	return (mouse.x >= pos.x && mouse.x < pos.x + (int)size.x
		&& mouse.y >= pos.y && mouse.y < pos.y + (int)size.y);
}

bool	click_fdf_row(t_gui *gui, t_vec2i mouse, t_vec2i *p)
{
	t_mesh		*fdf;
	t_vec2s		d;
	int			bw;
	int			gap;

	fdf = get_selected_fdf_mesh(gui);
	if (!fdf)
		return (false);
	d = gui->win.disp_size;
	bw = (ui_sx(gui->inspector.width - 18, d) - ui_sx(3, d)) / 2;
	gap = ui_sx(3, d);
	p->y += ui_sy(INSP_HDR_STEP, d);
	if (mat_hit_btn(gui, mouse, *p, vec2s(bw, ui_sy(18, d))))
	{
		fdf_switch_mode(fdf, gui->scene, FDF_MODE_HEIGHT);
		p->y += ui_sy(INSP_HDR_STEP + 26, d);
		return (true);
	}
	if (mat_hit_btn(gui, mouse, vec2i(p->x + bw + gap, p->y),
			vec2s(bw, ui_sy(18, d))))
	{
		fdf_switch_mode(fdf, gui->scene, FDF_MODE_PICTURE);
		p->y += ui_sy(INSP_HDR_STEP + 26, d);
		return (true);
	}
	p->y += ui_sy(INSP_HDR_STEP + 26, d);
	return (false);
}

bool	click_mat_slots(t_gui *gui, t_vec2i mouse, t_vec2i *p)
{
	t_vec2s	d;
	int		bw;
	int		bh;
	int		gap;

	d = gui->win.disp_size;
	bw = (ui_sx(gui->inspector.width - 18, d) - ui_sx(3, d)) / 2;
	bh = ui_sy(18, d);
	gap = ui_sx(3, d);
	if (mat_hit_btn(gui, mouse, *p, vec2s(bw, bh)))
		set_selected_group_slot(gui, 0);
	else if (mat_hit_btn(gui, mouse, vec2i(p->x + bw + gap, p->y),
			vec2s(bw, bh)))
	{
		ensure_slot_mat(gui, 1);
		set_selected_group_slot(gui, 1);
	}
	else if (mat_hit_btn(gui, mouse, vec2i(p->x, p->y + bh + gap),
			vec2s(bw, bh)))
	{
		ensure_slot_mat(gui, 2);
		set_selected_group_slot(gui, 2);
	}
	else if (mat_hit_btn(gui, mouse, vec2i(p->x + bw + gap, p->y + bh + gap),
			vec2s(bw, bh)))
	{
		set_selected_group_slot(gui, 3);
	}
	else
	{
		p->y += ui_sy(44, d);
		return (false);
	}
	if (gui->scene)
		scene_init_uv_flags(gui->scene);
	gui->render.dirty = true;
	p->y += ui_sy(44, d);
	return (true);
}
