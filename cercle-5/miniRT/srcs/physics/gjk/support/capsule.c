/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"

/**
 * @brief GJK support point for a capsule.
 */
t_vec3	gjk_support_capsule(const void *data, t_vec3 dir)
{
	const t_capsule	*cap;
	t_vec3			pole;
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
	return (vec3_add(pole, vec3_scale(dir, cap->radius / len)));
}
