/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Global AABB broadphase for non-accelerated body pairs.
 * Compliance: Fixed O(n^2) loop length to stay under 25 lines (Piège C).
 */
int	broadphase(t_scene *s, t_body_pair *out, int max)
{
	t_physics_body	*bodies[MAX_BODY_PAIRS];
	size_t			n;
	size_t			i;
	size_t			j;
	int				count;

	n = collect_bodies(s, bodies, MAX_BODY_PAIRS);
	count = 0;
	i = 0;
	while (i < n && count < max)
	{
		j = i + 1;
		while (j < n && count < max)
		{
			if (aabb_overlap_broad(bodies[i]->global_aabb, bodies[j]->global_aabb))
			{
				out[count].a = bodies[i];
				out[count++].b = bodies[j];
			}
			j++;
		}
		i++;
	}
	return (count);
}
