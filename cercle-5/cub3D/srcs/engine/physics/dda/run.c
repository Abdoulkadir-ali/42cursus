/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:44:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 22:39:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "gameplay.h"

static bool	step_loop(t_dda *d, t_map *map)
{
	while (1)
	{
		dda_step(d);
		if (d->map_x < 0 || d->map_y < 0 || (size_t)d->map_x >= map->size.x
			|| (size_t)d->map_y >= map->size.y)
			return (false);
		if (check_cell_content(d, map))
			return (true);
	}
}

static void	process_ray_interaction(t_dda *d, t_map *map, int *b, float *acc)
{
	if (try_portal(d, map))
	{
		*acc += d->perp_dist;
		(*b)++;
	}
	else if (try_mirror(d, map))
	{
		*acc += d->perp_dist;
		(*b)++;
	}
	else
		*b = MAX_RAY_BOUNCES + 1;
}

void	run_dda(t_dda *d, t_map *map)
{
	int		bounces;
	float	acc;

	acc = 0.0f;
	bounces = 0;
	while (bounces <= MAX_RAY_BOUNCES)
	{
		if (!step_loop(d, map))
		{
			d->hit_tile = 0;
			break ;
		}
		process_ray_interaction(d, map, &bounces, &acc);
	}
	d->perp_dist += acc;
}
