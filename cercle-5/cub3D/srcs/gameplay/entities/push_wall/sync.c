/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:38:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	set_push_grid(t_world *world, int i, t_vec2i pos)
{
	if (pos.x >= 0 && pos.y >= 0 && (size_t)pos.x < world->map->size.x
		&& (size_t)pos.y < world->map->size.y)
		world->push_grid[pos.y * world->map->size.x + pos.x] = i;
}

void	sync_push_grid(t_world *world)
{
	size_t		total;
	size_t		k;
	size_t		i;
	t_push_wall	*pw;

	if (!world->push_grid)
		return ;
	total = world->map->size.x * world->map->size.y;
	k = 0;
	while (k < total)
		world->push_grid[k++] = -1;
	i = 0;
	while (i < MAX_PUSH_WALLS)
	{
		pw = &world->push_walls[i];
		if (pw->active)
		{
			world->push_grid[pw->s.y * world->map->size.x + pw->s.x] = (int)i;
			set_push_grid(world, (int)i, (t_vec2i){(int)pw->s.x + pw->d.x,
				(int)pw->s.y + pw->d.y});
		}
		i++;
	}
}
