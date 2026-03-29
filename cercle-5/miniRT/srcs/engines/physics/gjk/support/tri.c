/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:15:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a standalone triangle.
 * Fetches vertices directly from the scene's triangle SoA (tri_soa).
 */
t_vec3	gjk_support_tri(const t_gjk_shape *s, t_vec3 dir)
{
	t_tri_array	*t;
	t_vec3		v[3];

	t = &s->scene->tri_soa;
	v[0] = vec3(t->vx[0][s->idx], t->vy[0][s->idx], t->vz[0][s->idx]);
	v[1] = vec3(t->vx[1][s->idx], t->vy[1][s->idx], t->vz[1][s->idx]);
	v[2] = vec3(t->vx[2][s->idx], t->vy[2][s->idx], t->vz[2][s->idx]);
	return (gjk_support_list(v, 3, dir));
}
