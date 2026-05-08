/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:42:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 23:33:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	render_raycast_scene(t_window *win, t_world *world)
{
	t_render_strip	strip;
	float			fov_rad;
	float			plane_len;

	if (world->map == NULL)
		return ;
	clear_z_buffer(win);
	fov_rad = world->player.fov * M_PI / 360.0f;
	plane_len = tanf(fov_rad);
	draw_planes(win, world, plane_len);
	init_render_strip(&strip, win, world);
	draw_strip(&strip);
	render_entities(win, world);
}
