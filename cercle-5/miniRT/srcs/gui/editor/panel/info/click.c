/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** Apply anim settings from [start] mesh to all sub-meshes in the group.
*/
static void	sync_group_anim(t_gui *gui, t_mesh_group *g)
{
	size_t		i;
	t_mesh_anim	src;

	src = gui->scene->meshes[g->start].anim;
	i = 0;
	while (i < g->sub_count)
	{
		gui->scene->meshes[g->start + i].anim = src;
		i++;
	}
}

/*
** < > clip selector buttons.
** < at x+8..x+20,  > at x+INSPECTOR_W-22..x+INSPECTOR_W-8
** y range: y_sel to y_sel+14
*/
static bool	handle_clip_select(t_gui *gui, t_vec2i mouse, int x,
		t_mesh_anim *ma)
{
	t_vec2s	d;
	int		y;
	size_t	n;

	d = gui->win.disp_size;
	y = ui_sy(232, d);
	n = gui->scene->clip_count;
	if (n == 0)
		return (false);
	if (mouse.y < y || mouse.y > (y + ui_sy(14, d)))
		return (false);
	if (mouse.x >= (x + ui_sx(4, d)) && mouse.x <= (x + ui_sx(22, d)))
	{
		if (ma->idx.i == 0)
			ma->idx.i = n - 1;
		else
			ma->idx.i--;
		return (true);
	}
	if (mouse.x >= (x + gui->inspector.width - ui_sx(26, d))
		&& mouse.x <= (x + gui->inspector.width - ui_sx(4, d)))
	{
		ma->idx.i++;
		if (ma->idx.i >= n)
			ma->idx.i = 0;
		return (true);
	}
	return (false);
}

bool	info_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_mesh_group	*g;
	t_mesh			*mesh;
	t_islider		speed_sl;
	t_mesh_anim		*ma;
	t_vec2s			d;
	int				x;
	t_vec2i			p;

	d = gui->win.disp_size;
	if (!gui->scene)
		return (false);
	if (gui->scene->group_count > 0
		&& gui->selection.index.i < gui->scene->group_count)
	{
		g = &gui->scene->groups[gui->selection.index.i];
		mesh = &gui->scene->meshes[g->mesh_start];
	}
	else if (gui->selection.index.i < gui->scene->mesh_count)
	{
		g = NULL;
		mesh = &gui->scene->meshes[gui->selection.index.i];
	}
	else
		return (false);
	if (!mesh->skeleton || mesh->bone_count == 0
		|| gui->scene->clip_count == 0)
		return (false);
	ma = &mesh->anim;
	x = d.x - gui->inspector.width;
	if (handle_clip_select(gui, mouse, x, ma))
	{
		if (g)
			sync_group_anim(gui, g);
		gui->anim_engine.mesh_count = 0;
		gui->render.dirty = true;
		return (true);
	}
	p = (t_vec2i){x, ui_sy(256, d)};
	speed_sl = (t_islider){
		.ptr = &ma->speed, .min = 0.0, .max = 3.0, .label = "Speed"};
	if (insp_row_click(gui, mouse, p, speed_sl))
	{
		if (g)
			sync_group_anim(gui, g);
		gui->render.dirty = true;
		return (true);
	}
	p.y += ui_sy(INSP_ROW_STEP, d);
	if (insp_toggle_click(gui, mouse, p))
	{
		ma->looping = !ma->looping;
		if (g)
			sync_group_anim(gui, g);
		gui->render.dirty = true;
		return (true);
	}
	p.y += ui_sy(INSP_ROW_STEP, d);
	if (insp_toggle_click(gui, mouse, p))
	{
		ma->paused = !ma->paused;
		if (g)
			sync_group_anim(gui, g);
		gui->render.dirty = true;
		return (true);
	}
	return (false);
}
