/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 07:28:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	calc_line_params(t_floor_data *d, float plane_len, t_vec2 params[3])
{
	float	p;
	t_vec2	pl;
	t_vec2	r[2];
	float	h;

	h = d->win->height / 2.0f - (d->player.render_pitch_offset
			* d->win->height);
	p = (float)d->y - h;
	if (fabsf(p) < 0.001f)
		return ;
	pl.x = -d->player.render_dir.y * plane_len;
	pl.y = d->player.render_dir.x * plane_len;
	r[0] = (t_vec2){d->player.render_dir.x - pl.x, d->player.render_dir.y
		- pl.y};
	r[1] = (t_vec2){d->player.render_dir.x + pl.x, d->player.render_dir.y
		+ pl.y};
	d->dist = (d->win->height * 0.5f * (0.66f / plane_len)) / fabsf(p);
	params[1].x = d->dist * (r[1].x - r[0].x) / (float)d->win->width;
	params[1].y = d->dist * (r[1].y - r[0].y) / (float)d->win->width;
	params[0].x = d->player.render_pos.x + d->dist * r[0].x;
	params[0].y = d->player.render_pos.y + d->dist * r[0].y;
	params[2] = (t_vec2){(float)(p > 0), 0};
}
