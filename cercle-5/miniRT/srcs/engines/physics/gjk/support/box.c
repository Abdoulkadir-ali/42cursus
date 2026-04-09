/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 16:14:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest corner of an oriented box along search direction.
 * Uses axes cached on the transform (updated each integration step).
 */
t_vec3	gjk_support_box(const void *data, t_vec3 dir)
{
	const t_box	*bx;
	t_vec3		p;

	bx = (const t_box *)data;
	p = bx->phys.center;
	if (vec3_dot(bx->transform.forward, dir) >= 0.0)
		p = vec3_add(p, vec3_scale(bx->transform.forward, bx->half_extents.x));
	else
		p = vec3_sub(p, vec3_scale(bx->transform.forward, bx->half_extents.x));
	if (vec3_dot(bx->transform.right, dir) >= 0.0)
		p = vec3_add(p, vec3_scale(bx->transform.right, bx->half_extents.y));
	else
		p = vec3_sub(p, vec3_scale(bx->transform.right, bx->half_extents.y));
	if (vec3_dot(bx->transform.up, dir) >= 0.0)
		p = vec3_add(p, vec3_scale(bx->transform.up, bx->half_extents.z));
	else
		p = vec3_sub(p, vec3_scale(bx->transform.up, bx->half_extents.z));
	return (p);
}
