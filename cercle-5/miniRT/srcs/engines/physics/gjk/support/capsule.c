/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest point of a capsule along the search direction.
 */
t_vec3	gjk_support_capsule(const void *data, t_vec3 dir)
{
	const t_capsule	*cap;
	t_vec3			pole;
	t_vec3			nd;
	double			len;

	cap = (const t_capsule *)data;
	if (vec3_dot(cap->axis, dir) >= 0.0)
		pole = vec3_add(cap->transform.pos,
				vec3_scale(cap->axis, cap->half_height));
	else
		pole = vec3_sub(cap->transform.pos,
				vec3_scale(cap->axis, cap->half_height));
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (pole);
	nd = vec3_scale(dir, 1.0 / len);
	return (vec3_add(pole, vec3_scale(nd, cap->radius)));
}
