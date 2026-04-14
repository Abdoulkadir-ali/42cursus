/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/* aabb_create_empty, aabb_union, aabb_expand_point are now static inline
   in includes/functions/helpers/maths.h — no .c body needed. */

/**
 * Computes the surface area of an Axis-Aligned Bounding Box.
 */
double	aabb_surface_area(t_aabb bbox)
{
	t_vec3	d;

	d = vec3_sub(bbox.max, bbox.min);
	if (d.x < 0 || d.y < 0 || d.z < 0)
		return (0);
	return (2 * (d.x * d.y + d.y * d.z + d.z * d.x));
}
