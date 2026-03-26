/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Main entry point for ray-cylinder intersection.
*/
bool	intersect_cylinder(const t_ray *ray, t_cylinder *cy, t_hit *hit)
{
	double	t_min;
	bool	hit_found;

	t_min = DBL_MAX;
	hit_found = false;
	if (check_body(ray, cy, &t_min, hit))
		hit_found = true;
	if (check_bottom_cap(ray, cy, &t_min, hit))
		hit_found = true;
	if (check_top_cap(ray, cy, &t_min, hit))
		hit_found = true;
	if (hit_found)
	{
		if (vec3_dot(ray->direction, hit->normal) > 0)
			hit->normal = vec3_scale(hit->normal, -1.0);
	}
	return (hit_found);
}
