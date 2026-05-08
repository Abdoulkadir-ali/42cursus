/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:42:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:38:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	clear_z_buffer(t_window *win)
{
	int	i;
	int	size;

	if (!win->z_buffer)
		return ;
	size = win->width * win->height;
	i = 0;
	while (i < size)
	{
		win->z_buffer[i] = INF;
		i++;
	}
}

void	init_render_strip(t_render_strip *s, t_window *win, t_world *world)
{
	float	fov_rad;
	float	plane_len;
	t_vec2	dir;

	dir = (t_vec2){world->player.render_dir.x, world->player.render_dir.y};
	fov_rad = world->player.fov * M_PI / 360.0f;
	plane_len = tanf(fov_rad);
	s->win = win;
	s->world = world;
	s->plane_len = plane_len;
	s->dir = (t_vec3){dir.x, dir.y, 0.0f};
	s->plane.x = -dir.y * plane_len;
	s->plane.y = dir.x * plane_len;
	s->start_x = 0;
	s->end_x = win->width;
}
