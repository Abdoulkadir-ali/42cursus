/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 05:05:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinder.h"

static bool	pf_is_collectible(char c)
{
	return (c == 'G' || c == 'M' || c == 'A' || c == 'P');
}

bool	pf_validate_map(const t_map *map, t_vec2 player_pos)
{
	t_vec2i	p;
	t_vec2	goal;
	bool	pass;

	p.y = -1;
	while (++p.y < (int)map->height)
	{
		p.x = -1;
		while (++p.x < (int)map->width)
		{
			if (pf_is_collectible(map->grid[p.y][p.x]))
			{
				goal = (t_vec2){(float)p.x + 0.5f, (float)p.y + 0.5f};
				pass = pf_has_path(map, player_pos, goal, false);
				if (!pass)
					return (false);
			}
		}
	}
	return (true);
}
