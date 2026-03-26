/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
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
 * @brief GJK support point for a pyramid. Calculates corners on-the-fly.
 */
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir)
{
	const t_pyramid	*py;
	t_vec3			v[5];
	t_vec3			basis[2];
	double			h;

	py = (const t_pyramid *)data;
	h = py->base_size * 0.5;
	basis[0] = (fabs(py->up.y) < 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
	basis[0] = vec3_norm(vec3_cross(py->up, basis[0]));
	basis[1] = vec3_cross(basis[0], py->up);
	v[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(basis[0], h)),
			vec3_scale(basis[1], h));
	v[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(basis[0], -h)),
			vec3_scale(basis[1], h));
	v[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(basis[0], -h)),
			vec3_scale(basis[1], -h));
	v[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(basis[0], h)),
			vec3_scale(basis[1], -h));
	v[4] = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
	return (gjk_support_list(v, 5, dir));
}
