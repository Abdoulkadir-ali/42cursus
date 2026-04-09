/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:56:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_anim_selector(t_gui *gui, t_vec2i pos, t_mesh_anim *ma,
		t_scene *scene)
{
	t_vec2s			d;
	char			buf[64];
	t_animation		*clip;
	const char		*name;

	d = gui->win.disp_size;
	mlx_string_put_c(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d), pos.y,
		COL_ACCENT, "<");
	mlx_string_put_c(gui->win.mlx, gui->win.win,
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
	mlx_string_put_c(gui->win.mlx, gui->win.win, pos.x + ui_sx(24, d), pos.y,
		COL_TEXT, buf);
}

static void	draw_anim_toggles(t_gui *gui, t_vec2i p, t_mesh *mesh)
{
	t_vec2s	d;

	d = gui->win.disp_size;
	draw_insp_toggle_row(gui, vec2i(p.x + ui_sx(8, d), p.y), "Loop",
		mesh->anim.looping);
	p.y += ui_sy(INSP_ROW_STEP, d);
	draw_insp_toggle_row(gui, vec2i(p.x + ui_sx(8, d), p.y), "Paused",
		mesh->anim.paused);
}

void	draw_anim_section(t_gui *gui, t_vec2i pos, t_mesh *mesh)
{
	t_vec2s		d;
	t_vec2i		p;
	char		buf[32];

	d = gui->win.disp_size;
	p = (t_vec2i){pos.x, ui_sy(210, d)};
	draw_insp_header(gui, (t_vec2i){p.x + ui_sx(8, d), p.y}, "Animation");
	p.y += ui_sy(INSP_HDR_STEP, d);
	if (gui->scene->clip_count == 0)
	{
		mlx_string_put_c(gui->win.mlx, gui->win.win, p.x + ui_sx(8, d), p.y,
			COL_TEXT, "No animation clips");
		return ;
	}
	snprintf(buf, sizeof(buf), "%zu", gui->scene->clip_count);
	draw_info_row(gui, p, "Clips:", buf);
	p.y += ui_sy(22, d);
	draw_anim_selector(gui, p, &mesh->anim, gui->scene);
	p.y += ui_sy(INSP_ROW_STEP, d);
	draw_insp_row(gui, p, (t_islider){"Speed", 0, 3, &mesh->anim.speed, NULL});
	p.y += ui_sy(INSP_ROW_STEP, d);
	draw_anim_toggles(gui, p, mesh);
}
