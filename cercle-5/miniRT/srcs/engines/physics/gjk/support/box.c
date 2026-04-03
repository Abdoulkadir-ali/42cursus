/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest corner of an oriented box along search direction.
 */
t_vec3	gjk_support_box(const void *data, t_vec3 dir)
{
	const t_box	*bx;
	t_vec3		ax[3];
	t_vec3		p;

	bx = (const t_box *)data;
	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	p = bx->phys.center;
	if (vec3_dot(ax[0], dir) >= 0.0)
		p = vec3_add(p, vec3_scale(ax[0], bx->half_extents.x));
	else
		p = vec3_sub(p, vec3_scale(ax[0], bx->half_extents.x));
	if (vec3_dot(ax[1], dir) >= 0.0)
		p = vec3_add(p, vec3_scale(ax[1], bx->half_extents.y));
	else
		p = vec3_sub(p, vec3_scale(ax[1], bx->half_extents.y));
	if (vec3_dot(ax[2], dir) >= 0.0)
		p = vec3_add(p, vec3_scale(ax[2], bx->half_extents.z));
	else
		p = vec3_sub(p, vec3_scale(ax[2], bx->half_extents.z));
	return (p);
}
