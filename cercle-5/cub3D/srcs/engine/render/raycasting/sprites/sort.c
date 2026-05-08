/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:16:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:32:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static void	fill_dist(t_world *world, size_t *indices, float *dist)
{
	size_t	i;

	i = 0;
	while (i < world->entity_count)
	{
		indices[i] = i;
		dist[i] = powf(world->player.render_pos.x
				- world->entities[indices[i]].pos.x, 2)
			+ powf(world->player.render_pos.y
				- world->entities[indices[i]].pos.y, 2);
		i++;
	}
}

void	sort_entities(t_world *world, size_t *indices, float *distances)
{
	size_t	i;
	size_t	j;
	size_t	tmp_idx;
	float	tmp_dist;

	fill_dist(world, indices, distances);
	i = 0;
	while (world->entity_count > 0 && i < world->entity_count - 1)
	{
		j = i + 1;
		while (j < world->entity_count)
		{
			if (distances[i] < distances[j])
			{
				tmp_dist = distances[i];
				distances[i] = distances[j];
				distances[j] = tmp_dist;
				tmp_idx = indices[i];
				indices[i] = indices[j];
				indices[j] = tmp_idx;
			}
			j++;
		}
		i++;
	}
}
