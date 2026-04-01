/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes the Axis-Aligned Bounding Box for a plane (infinite).
 */
t_aabb	plane_aabb(void)
{
	t_aabb	bbox;

	bbox.min = vec3(-MAX_VALUE, -MAX_VALUE, -MAX_VALUE);
	bbox.max = vec3(MAX_VALUE, MAX_VALUE, MAX_VALUE);
	return (bbox);
}
