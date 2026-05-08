/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:38:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:07:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	tick_push_walls(t_world *world, float dt)
{
	size_t		i;
	t_push_wall	*pw;
	t_vec2i		t;

	i = 0;
	while (i < MAX_PUSH_WALLS)
	{
		pw = &world->push_walls[i++];
		if (!pw->active)
			continue ;
		pw->offset += PUSH_WALL_SPEED * dt;
		if (pw->offset >= 1.0f)
		{
			pw->offset = 1.0f;
			t.x = (int)pw->s.x + pw->d.x;
			t.y = (int)pw->s.y + pw->d.y;
			world->map->grid[pw->s.y][pw->s.x] = '0';
			world->map->grid[t.y][t.x] = '1';
			pw->active = false;
		}
	}
}
