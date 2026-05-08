/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:35:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 07:35:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw_planes(t_window *win, t_world *world, float plane_len)
{
	t_draw_line_data	d;
	t_player_snapshot	p;
	int					y;

	p = (t_player_snapshot){world->player.render_pos, world->player.render_dir,
		world->player.render_pitch_offset, world->player.render_pos_z};
	d.player_ref = p;
	d.p_len = plane_len;
	y = 0;
	while (y < win->height)
	{
		draw_plane_line(win, world, y, &d);
		y++;
	}
}
