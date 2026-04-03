/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:27:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * Checks if a sphere collides with a single triangle (v0, v1, v2).
 * Returns true if a collision is found that is closer than *min_dist_sq.
 */
bool	test_sphere_triangle(const t_sphere *s, t_vec3 v[3],
			t_collision *col)
{
	t_vec3	closest;
	t_vec3	diff;
	double	dist_sq;
	double	r;
	double	dist;

	closest = closest_point_on_triangle(s->transform.pos, v[0], v[1], v[2]);
	diff = vec3_sub(s->transform.pos, closest);
	dist_sq = vec3_mag_sq(diff);
	r = sqrt(s->radius_sq);
	if (dist_sq < r * r && dist_sq < col->min_dist_sq)
	{
		col->min_dist_sq = dist_sq;
		dist = sqrt(dist_sq);
		col->normal = vec3_scale(diff, 1.0 / (dist + 1e-6));
		col->pen = r - dist;
		return (true);
	}
	return (false);
}
