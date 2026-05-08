/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:16:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 23:54:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static t_vec2	get_plane(t_world *world)
{
	float	fov_rad;
	float	plen;
	t_vec2	pl;

	fov_rad = world->player.fov * M_PI / 360.0f;
	plen = tanf(fov_rad);
	pl.x = -world->player.render_dir.y * plen;
	pl.y = world->player.render_dir.x * plen;
	return (pl);
}

void	calc_sprite_pos(t_window *win, t_world *world, t_entity *ent,
		t_vec2 *transform)
{
	t_vec2	rel;
	t_vec2	pl;
	float	f;
	float	tr[2];

	rel.x = ent->pos.x - world->player.render_pos.x;
	rel.y = ent->pos.y - world->player.render_pos.y;
	pl = get_plane(world);
	f = 1.0f / (pl.x * world->player.render_dir.y
			- world->player.render_dir.x * pl.y);
	tr[0] = f * (world->player.render_dir.y * rel.x
			- world->player.render_dir.x * rel.y);
	tr[1] = f * (-pl.y * rel.x + pl.x * rel.y);
	transform->x = tr[0];
	transform->y = tr[1];
	(void)win;
}
