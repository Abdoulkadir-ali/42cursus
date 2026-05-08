/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:36:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <math.h>

static void	calculate_transform(t_world *world, t_vec3 rel, float *tr, float *plen)
{
	t_vec2	pl;
	float	f;

	f = world->player.fov * M_PI / 360.0f;
	*plen = tanf(f);
	pl.x = -world->player.render_dir.y * (*plen);
	pl.y = world->player.render_dir.x * (*plen);
	f = 1.0f / (pl.x * world->player.render_dir.y - world->player.render_dir.x
			* pl.y);
	tr[0] = f * (world->player.render_dir.y * rel.x - world->player.render_dir.x
			* rel.y);
	tr[1] = f * (-pl.y * rel.x + pl.x * rel.y);
}

t_vec2	project_to_screen(t_window *win, t_world *world, t_vec3 p)
{
	t_vec3	rel;
	float	tr[2];
	float	plen;

	rel.x = p.x - world->player.render_pos.x;
	rel.y = p.y - world->player.render_pos.y;
	calculate_transform(world, rel, tr, &plen);
	if (tr[1] <= 0.1f)
		return ((t_vec2){-1, -1});
	return ((t_vec2){(float)(win->width / 2) * (1.0f + tr[0] / tr[1]),
		(float)win->height / 2.0f - (world->player.render_pitch_offset
			* (float)win->height) + ((p.z - world->player.render_pos_z) / tr[1])
		* (float)win->height * (0.66f / plen)});
}

