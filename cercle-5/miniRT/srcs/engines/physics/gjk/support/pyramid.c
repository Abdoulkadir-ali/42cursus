/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:19:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a pyramid.
 * Calculates corners and apex dynamically from SoA data.
 */
t_vec3	gjk_support_pyramid(const t_gjk_shape *s, t_vec3 dir)
{
	t_pyramid	py;
	t_vec3		v[5];
	t_vec3		basis[2];

	py = unpack_pyramid(&s->scene->primitives, s->idx);
	vec3_orthonormal_basis(py.up, &basis[0], &basis[1]);
	v[0] = vec3_add(vec3_add(py.pos, vec3_scale(basis[0], py.size)),
			vec3_scale(basis[1], py.size));
	v[1] = vec3_add(vec3_add(py.pos, vec3_scale(basis[0], -py.size)),
			vec3_scale(basis[1], py.size));
	v[2] = vec3_add(vec3_add(py.pos, vec3_scale(basis[0], -py.size)),
			vec3_scale(basis[1], -py.size));
	v[3] = vec3_add(vec3_add(py.pos, vec3_scale(basis[0], py.size)),
			vec3_scale(basis[1], -py.size));
	v[4] = vec3_add(py.pos, vec3_scale(py.up, py.height));
	return (gjk_support_list(v, 5, dir));
}
