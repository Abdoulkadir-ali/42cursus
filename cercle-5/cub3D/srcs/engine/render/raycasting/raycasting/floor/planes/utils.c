/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:34:52 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 23:34:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	set_eye_and_dist(t_draw_line_data *d, t_player_snapshot *p,
		t_window *win, float plane_len)
{
	if (d->is_floor)
		d->eye_h = 0.5f + p->render_pos_z;
	else
		d->eye_h = WALL_HEIGHT - 0.5f - p->render_pos_z;
	if (d->eye_h < 0.05f)
		d->eye_h = 0.05f;
	d->dist = (win->height * d->eye_h * (0.66f / plane_len)) / fabsf(d->p);
}

void	prepare_line_data(t_draw_line_data *d, t_window *win,
		t_player_snapshot *p, int y)
{
	float	p_len;

	p_len = d->p_len;
	d->horizon = (float)win->height / 2.0f - (p->render_pitch_offset
			* win->height);
	d->p = (float)y - d->horizon;
	if (fabsf(d->p) < 0.0001f)
		return ;
	d->is_floor = (d->p > 0.0f);
	d->plane = (t_vec2){-p->render_dir.y * p_len, p->render_dir.x * p_len};
	d->ray_l = (t_vec2){p->render_dir.x - d->plane.x, p->render_dir.y
		- d->plane.y};
	d->ray_r = (t_vec2){p->render_dir.x + d->plane.x, p->render_dir.y
		+ d->plane.y};
	set_eye_and_dist(d, p, win, p_len);
	d->floor_pos = (t_vec2){p->render_pos.x + d->dist * d->ray_l.x,
		p->render_pos.y + d->dist * d->ray_l.y};
	d->floor_step = (t_vec2){d->dist * (d->ray_r.x - d->ray_l.x) / win->width,
		d->dist * (d->ray_r.y - d->ray_l.y) / win->width};
}
