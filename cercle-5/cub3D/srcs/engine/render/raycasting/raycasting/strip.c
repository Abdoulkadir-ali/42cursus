/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 22:41:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "physics.h"

static int	collect_ray_hits(t_render_strip *s, t_dda *hits, t_vec2 ray)
{
	int	n;

	init_dda(&hits[0], s->world->player.render_pos, ray);
	n = 0;
	while (n < 4)
	{
		run_dda(&hits[n], s->world->map);
		if (hits[n].hit_tile == 0 || !is_door_tile(hits[n].hit_tile)
			|| door_open_at(s->world->map, hits[n].map_x,
				hits[n].map_y) == 0.0f)
		{
			n++;
			break ;
		}
		n++;
		if (n < 4)
			hits[n] = hits[n - 1];
	}
	return (n);
}

static void	draw_collected_hits(t_render_col *rc, t_dda *hits, int num_hits,
				float plane_len)
{
	while (num_hits > 0)
	{
		num_hits--;
		rc->dda = &hits[num_hits];
		draw_column(rc, plane_len, false);
	}
}

void	*draw_strip(void *arg)
{
	t_render_strip	*s;
	t_render_col	rc;
	t_dda			hits[4];
	int				num_hits;
	int				x;

	s = (t_render_strip *)arg;
	rc.win = s->win;
	rc.world = s->world;
	x = s->start_x;
	while (x < s->end_x)
	{
		rc.screen_x = x;
		rc.ray.x = s->dir.x + s->plane.x
			* (2.0f * (float)x / (float)s->win->width - 1.0f);
		rc.ray.y = s->dir.y + s->plane.y
			* (2.0f * (float)x / (float)s->win->width - 1.0f);
		num_hits = collect_ray_hits(s, hits, rc.ray);
		draw_collected_hits(&rc, hits, num_hits, s->plane_len);
		x++;
	}
	return (NULL);
}
