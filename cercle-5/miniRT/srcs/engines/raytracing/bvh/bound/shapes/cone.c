/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes the Axis-Aligned Bounding Box for a cone.
 */
t_aabb	cone_aabb(t_cone *co)
{
	t_aabb	bbox;
	double	r;
	double	h;

	r = co->transform.scale.x;
	h = co->transform.scale.y;
	bbox.min = vec3_sub(co->transform.pos, vec3(r, h, r));
	bbox.max = vec3_add(co->transform.pos, vec3(r, h, r));
	return (bbox);
}
