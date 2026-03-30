/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes the Axis-Aligned Bounding Box for a cylinder.
 */
t_aabb	cylinder_aabb(t_cylinder *cy)
{
	t_aabb	bbox;
	double	r;
	double	h;

	r = cy->transform.scale.x;
	h = cy->transform.scale.y;
	bbox.min = vec3_sub(cy->transform.pos, vec3(r, h, r));
	bbox.max = vec3_add(cy->transform.pos, vec3(r, h, r));
	return (bbox);
}
