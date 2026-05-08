/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   los.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:26:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static bool	is_blocked(t_world *world, t_vec2 pos)
{
	char	c;

	c = world->map->grid[(int)pos.y][(int)pos.x];
	return (c != '0' && c != 'O');
}

bool	check_los(t_world *world, t_vec2 a, t_vec2 b)
{
	t_vec2	dir;
	t_vec2	pos;
	float	dist;
	float	i;

	dir = (t_vec2){b.x - a.x, b.y - a.y};
	dist = sqrtf(dir.x * dir.x + dir.y * dir.y);
	if (dist < 0.01f)
		return (true);
	dir.x /= dist;
	dir.y /= dist;
	pos = a;
	i = 0;
	while (i < dist)
	{
		pos.x += dir.x * 0.1f;
		pos.y += dir.y * 0.1f;
		if (is_blocked(world, pos))
			return (false);
		i += 0.1f;
	}
	return (true);
}
