/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_bbox_info(t_gui *gui, t_mesh *mesh, t_vec2i pos, int *y)
{
	t_vec2s	d;
	char	buf[64];

	d = gui->win.disp_size;
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.min.x, mesh->bbox.min.y, mesh->bbox.min.z);
	*y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "BBox min:", buf);
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.max.x, mesh->bbox.max.y, mesh->bbox.max.z);
	*y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "BBox max:", buf);
}

static void	draw_anim_selector(t_gui *gui, t_vec2i pos, t_mesh_anim *ma,
		t_scene *scene)
{
	t_vec2s			d;
	char			buf[64];
	t_animation		*clip;
	const char		*name;

	d = gui->win.disp_size;
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d), pos.y,
		COL_ACCENT, "<");
	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x + gui->inspector.width - ui_sx(22, d),
		pos.y, COL_ACCENT, ">");
	if (ma->idx.i < scene->clip_count)
	{
		clip = &scene->clips[ma->idx.i];
		name = "(unnamed)";
		if (clip->name && clip->name[0])
			name = clip->name;
		snprintf(buf, sizeof(buf), "%.18s [%zu/%zu]",
			name, ma->idx.i + 1, scene->clip_count);
	}
	else
		snprintf(buf, sizeof(buf), "none [%zu clips]", scene->clip_count);
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + ui_sx(24, d), pos.y,
		COL_TEXT, buf);
}

static void	draw_anim_section(t_gui *gui, t_vec2i pos, t_mesh *mesh)
{
	t_vec2s		d;
	t_islider	speed_sl;
	t_vec2i		p;
	char		buf[32];

	d = gui->win.disp_size;
	p = (t_vec2i){pos.x, ui_sy(210, d)};
	draw_insp_header(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, "Animation");
	p.y += ui_sy(INSP_HDR_STEP, d);
	if (gui->scene->clip_count == 0)
	{
		mlx_string_put(gui->win.mlx, gui->win.win, p.x + ui_sx(8, d), p.y,
			COL_TEXT, "No animation clips");
		return ;
	}
	snprintf(buf, sizeof(buf), "%zu", gui->scene->clip_count);
	draw_info_row(gui, p, "Clips:", buf);
	p.y += ui_sy(22, d);
	draw_anim_selector(gui, p, &mesh->anim, gui->scene);
	p.y += ui_sy(INSP_ROW_STEP, d);
	speed_sl = (t_islider){.ptr = &mesh->anim.speed, .min = 0.0, .max = 3.0,
		.label = "Speed"};
	draw_insp_row(gui, p, speed_sl);
	p.y += ui_sy(INSP_ROW_STEP, d);
	draw_insp_toggle_row(gui, vec2i(p.x + ui_sx(8, d), p.y), "Loop",
		mesh->anim.looping);
	p.y += ui_sy(INSP_ROW_STEP, d);
	draw_insp_toggle_row(gui, vec2i(p.x + ui_sx(8, d), p.y), "Paused",
		mesh->anim.paused);
}

static void	draw_mesh_basic_info(t_gui *gui, t_mesh_group *g, t_mesh *mesh,
				t_vec2i pos, int *y)
{
	char	buf[64];
	t_vec2s	d;

	d = gui->win.disp_size;
	if (g && g->name)
		snprintf(buf, sizeof(buf), "%.24s", g->name);
	else if (mesh->name)
		snprintf(buf, sizeof(buf), "%.24s", mesh->name);
	else
		snprintf(buf, sizeof(buf), "(unnamed)");
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "Name:", buf);
	if (g)
		snprintf(buf, sizeof(buf), "%zu", g->mesh_count);
	else
		snprintf(buf, sizeof(buf), "1");
	*y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "Sub-meshes:", buf);
	snprintf(buf, sizeof(buf), "%zu", mesh->vertex_count);
	*y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "Vertices:", buf);
	snprintf(buf, sizeof(buf), "%zu", mesh->tri_count);
	*y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "Triangles:", buf);
}

static void	set_mesh_ptr(t_gui *gui, t_mesh_group **g, t_mesh **mesh)
{
	if (gui->scene->group_count > 0
		&& gui->selection.index.i < gui->scene->group_count)
	{
		*g = &gui->scene->groups[gui->selection.index.i];
		*mesh = &gui->scene->meshes[(*g)->mesh_start];
	}
	else if (gui->selection.index.i < gui->scene->mesh_count)
	{
		*g = NULL;
		*mesh = &gui->scene->meshes[gui->selection.index.i];
	}
}

void	draw_mesh_info_panel(t_gui *gui, t_vec2i pos)
{
	t_vec2s			d;
	t_mesh_group	*g;
	t_mesh			*mesh;
	int				y;

	d = gui->win.disp_size;
	g = NULL;
	mesh = NULL;
	if (!gui->scene || gui->selection.index.error)
		return ;
	set_mesh_ptr(gui, &g, &mesh);
	if (!mesh)
		return ;
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d),
		ui_sy(88, d), COL_HOVER, "MESH INFO");
	y = ui_sy(106, d);
	draw_mesh_basic_info(gui, g, mesh, pos, &y);
	draw_bbox_info(gui, mesh, pos, &y);
	if (mesh->skeleton && mesh->bone_count > 0)
		draw_anim_section(gui, pos, mesh);
}
