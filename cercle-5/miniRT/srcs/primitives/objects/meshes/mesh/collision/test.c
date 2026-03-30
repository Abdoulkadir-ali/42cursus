/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "physics.h"
#include "mesh.h"

/**
 * Checks if a sphere collides with a single triangle (v0, v1, v2).
 * Returns true if a collision is found that is closer than *min_dist_sq.
 */
bool	test_sphere_triangle(const struct s_sphere *s, t_vec3 v[3],
			t_vec3 *out_normal, double *out_pen, double *min_dist_sq)
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
	if (dist_sq < r * r && dist_sq < *min_dist_sq)
	{
		*min_dist_sq = dist_sq;
		dist = sqrt(dist_sq);
		if (out_normal)
			*out_normal = vec3_scale(diff, 1.0 / (dist + 1e-6));
		if (out_pen)
			*out_pen = r - dist;
		return (true);
	}
	return (false);
}
