/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:45:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:48:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

bool	try_portal(t_dda *d, t_map *map)
{
	int		idx;
	int		pair;
	t_vec2i	target;
	t_vec3	new_origin;

	if (!map->portal_pair || d->hit_tile != 'p')
		return (false);
	idx = d->map_y * (int)map->size.x + d->map_x;
	pair = map->portal_pair[idx];
	if (pair < 0)
		return (false);
	target.x = pair % (int)map->size.x;
	target.y = pair / (int)map->size.x;
	new_origin.x = d->hit_pos.x + (float)(target.x - d->map_x);
	new_origin.y = d->hit_pos.y + (float)(target.y - d->map_y);
	new_origin.x += d->ray.x * BOUNCE_EPS;
	new_origin.y += d->ray.y * BOUNCE_EPS;
	new_origin.z = 0.0f;
	init_dda(d, new_origin, d->ray);
	return (true);
}

bool	try_mirror(t_dda *d, t_map *map)
{
	t_vec2	new_ray;
	t_vec3	new_origin;

	(void)map;
	if (d->hit_tile != 'm')
		return (false);
	new_ray = d->ray;
	if (d->side == 0)
		new_ray.x = -new_ray.x;
	else
		new_ray.y = -new_ray.y;
	new_origin.x = d->hit_pos.x + new_ray.x * BOUNCE_EPS;
	new_origin.y = d->hit_pos.y + new_ray.y * BOUNCE_EPS;
	new_origin.z = 0.0f;
	init_dda(d, new_origin, new_ray);
	return (true);
}
