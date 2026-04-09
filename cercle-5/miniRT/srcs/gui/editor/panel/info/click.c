/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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

static bool	handle_clip_select(t_gui *gui, t_vec2i mouse, int x,
		t_mesh_anim *ma)
{
	t_vec2s	d;
	int		y;
	size_t	n;

	d = gui->win.disp_size;
	y = ui_sy(232, d);
	n = gui->scene->clip_count;
	if (n == 0 || mouse.y < y || mouse.y > (y + ui_sy(14, d)))
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
		ma->idx.i = (ma->idx.i + 1) % n;
		return (true);
	}
	return (false);
}

static bool	handle_anim_ctrl(t_gui *gui, t_vec2i m, t_mesh_anim *ma, t_vec2i p)
{
	t_vec2s	d;

	d = gui->win.disp_size;
	if (insp_toggle_click(gui, m, p))
	{
		ma->looping = !ma->looping;
		return (true);
	}
	p.y += ui_sy(INSP_ROW_STEP, d);
	if (insp_toggle_click(gui, m, p))
	{
		ma->paused = !ma->paused;
		return (true);
	}
	return (false);
}

static t_mesh	*get_m_ptr(t_gui *gui, t_mesh_group **g)
{
	t_scene	*sc;

	sc = gui->scene;
	if (gui->selection.type == TYPE_MESH
		&& gui->selection.index.i < sc->group_count)
	{
		*g = &sc->groups[gui->selection.index.i];
		return (&sc->meshes[(*g)->mesh_start]);
	}
	if (gui->selection.index.i < sc->mesh_count)
	{
		*g = NULL;
		return (&sc->meshes[gui->selection.index.i]);
	}
	return (NULL);
}

bool	info_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_mesh_group	*g;
	t_mesh			*m;
	t_vec2i			p;
	int				x;

	if (!gui->scene || gui->selection.index.error)
		return (false);
	m = get_m_ptr(gui, &g);
	if (!m || !m->skeleton || m->bone_count == 0 || gui->scene->clip_count == 0)
		return (false);
	x = gui->win.disp_size.x - gui->inspector.width;
	if (handle_clip_select(gui, mouse, x, &m->anim))
	{
		if (g)
			sync_group_anim(gui, g);
		return (gui->anim_engine.mesh_count = 0, true);
	}
	p = vec2i(x, ui_sy(256, gui->win.disp_size));
	if (insp_row_click(gui, mouse, p,
			(t_islider){"Speed", 0, 3, &m->anim.speed, 0}))
		return (sync_group_anim(gui, g), gui->render.dirty = true, true);
	p.y += ui_sy(INSP_ROW_STEP, gui->win.disp_size);
	if (handle_anim_ctrl(gui, mouse, &m->anim, p))
		return (sync_group_anim(gui, g), gui->render.dirty = true, true);
	return (false);
}
