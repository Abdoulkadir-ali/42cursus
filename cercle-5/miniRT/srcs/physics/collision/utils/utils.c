/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

/**
 * @brief Checks if two Axis-Aligned Bounding Boxes (AABB) overlap.
 */
bool	aabb_overlap(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return (false);
	return (true);
}

/**
 * @brief Utility for checking if a GJK shape is colliding with any of the
 * planes defined in the scene.
 */
int	gjk_vs_all_planes(t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
		t_scene *s, t_contact *c, int count, int max)
{
	int	p;

	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += gjk_vs_plane(sa, ba, ta, &s->planes[p], &c[count]);
		p++;
	}
	return (count);
}
