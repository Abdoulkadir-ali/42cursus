/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 21:55:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 23:37:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	core_crosshair(t_window *win, t_world *world, size_t target)
{
	t_vec2i			p;
	t_vec2i			tex_p;
	unsigned int	pix;
	float			cent_x;
	float			cent_y;

	cent_x = (float)(win->width / 2 - (int)target / 2);
	cent_y = (float)(win->height / 2 - (int)target / 2);
	p.y = -1;
	while ((size_t)++p.y < target)
	{
		p.x = -1;
		while ((size_t)++p.x < target)
		{
			tex_p.x = (int)((float)p.x / (float)target
					* (float)world->crosshair.size.x);
			tex_p.y = (int)((float)p.y / (float)target
					* (float)world->crosshair.size.y);
			pix = world->crosshair.data[tex_p.y * world->crosshair.size.x
				+ tex_p.x];
			if ((pix >> 24) != 0)
				put_pixel(win, (t_vec2){cent_x + p.x, cent_y + p.y},
					v3_col(pix));
		}
	}
}

void	render_crosshair(t_window *win, t_world *world)
{
	t_vec2	center;

	center.x = (float)(win->width / 2);
	center.y = (float)(win->height / 2);
	put_pixel(win, center, (t_vec3){255, 255, 0});
	put_pixel(win, (t_vec2){center.x + 1, center.y}, (t_vec3){255, 255, 0});
	put_pixel(win, (t_vec2){center.x, center.y + 1}, (t_vec3){255, 255, 0});
	put_pixel(win, (t_vec2){center.x + 1, center.y + 1}, (t_vec3){255, 255, 0});
	if (world->crosshair.data == NULL)
		return ;
	core_crosshair(win, world, 32);
}
