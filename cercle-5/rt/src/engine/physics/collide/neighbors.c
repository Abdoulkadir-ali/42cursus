/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:20:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

void	collide_neighbors(t_app *app, int bi)
{
	t_phys_world	*w;
	t_body		*a;
	int		ix;
	int		iy;
	int		iz;
	int		dx;
	int		dy;
	int		dz;
	int		c;
	int		k;
	int		other;

	w = &app->phys;
	a = &w->bodies[bi];
	ix = (int)((a->pos.x - w->bmin.x) / w->cell_size);
	iy = (int)((a->pos.y - w->bmin.y) / w->cell_size);
	iz = (int)((a->pos.z - w->bmin.z) / w->cell_size);
	dz = -1;
	while (dz <= 1)
	{
		if (iz + dz >= 0 && iz + dz < w->nz)
		{
			dy = -1;
			while (dy <= 1)
			{
				if (iy + dy >= 0 && iy + dy < w->ny)
				{
					dx = -1;
					while (dx <= 1)
					{
						if (ix + dx >= 0 && ix + dx < w->nx)
						{
							c = ((iz + dz) * w->ny + (iy + dy)) * w->nx
								+ (ix + dx);
							k = w->cell_start[c];
							while (k < w->cell_start[c + 1])
							{
								other = w->cell_items[k];
								if (other > bi)
									resolve_pair(app, a, &w->bodies[other]);
								k++;
							}
						}
						dx++;
					}
				}
				dy++;
			}
		}
		dz++;
	}
}
