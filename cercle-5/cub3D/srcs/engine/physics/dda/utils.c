/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 22:31:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/physics.h"

void	set_tex_idx(t_dda *d, t_map *map)
{
	d->tex_idx = TEX_WE;
	if (d->side == 0 && d->step_x > 0)
		d->tex_idx = TEX_EA;
	if (d->side == 1)
	{
		d->tex_idx = TEX_NO;
		if (d->step_y > 0)
			d->tex_idx = TEX_SO;
	}
	if (is_door_tile(d->hit_tile))
		d->tex_idx = TEX_DOOR;
	(void)map;
}

void	dda_step(t_dda *d)
{
	if (d->side_dist_x < d->side_dist_y)
	{
		d->side_dist_x += d->delta_dist_x;
		d->map_x += d->step_x;
		d->side = 0;
	}
	else
	{
		d->side_dist_y += d->delta_dist_y;
		d->map_y += d->step_y;
		d->side = 1;
	}
}

void	finalize_axis_hit(t_dda *d, t_map *map)
{
	d->perp_dist = d->side_dist_y - d->delta_dist_y;
	if (d->side == 0)
		d->perp_dist = d->side_dist_x - d->delta_dist_x;
	d->hit_tile = '1';
	if (d->map_x >= 0 && d->map_y >= 0 && (size_t)d->map_x < map->size.x
		&& (size_t)d->map_y < map->size.y)
		d->hit_tile = map->grid[d->map_y][d->map_x];
	set_tex_idx(d, map);
	d->hit_pos.x = d->origin.x + d->perp_dist * d->ray.x;
	d->hit_pos.y = d->origin.y + d->perp_dist * d->ray.y;
	d->hit_pos.z = 0.0f;
}
