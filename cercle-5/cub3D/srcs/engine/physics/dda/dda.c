/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:50:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	init_dda(t_dda *d, t_vec3 pos, t_vec2 ray)
{
	d->origin = pos;
	d->ray = ray;
	d->map_x = (int)pos.x;
	d->map_y = (int)pos.y;
	d->delta_dist_x = FLT_MAX;
	if (ray.x != 0.0f)
		d->delta_dist_x = fabsf(1.0f / ray.x);
	d->delta_dist_y = FLT_MAX;
	if (ray.y != 0.0f)
		d->delta_dist_y = fabsf(1.0f / ray.y);
	d->step_x = 1;
	d->side_dist_x = (d->map_x + 1.0f - pos.x) * d->delta_dist_x;
	if (ray.x < 0.0f)
	{
		d->step_x = -1;
		d->side_dist_x = (pos.x - (float)d->map_x) * d->delta_dist_x;
	}
	d->step_y = 1;
	d->side_dist_y = (d->map_y + 1.0f - pos.y) * d->delta_dist_y;
	if (ray.y < 0.0f)
	{
		d->step_y = -1;
		d->side_dist_y = (pos.y - (float)d->map_y) * d->delta_dist_y;
	}
}
