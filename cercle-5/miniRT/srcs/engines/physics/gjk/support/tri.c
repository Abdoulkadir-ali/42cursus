/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:40:00 by abdoali          ###   ########.fr       */
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
	v[0] = vec3(t->vx0[s->idx], t->vy0[s->idx], t->vz0[s->idx]);
	v[1] = vec3(t->vx1[s->idx], t->vy1[s->idx], t->vz1[s->idx]);
	v[2] = vec3(t->vx2[s->idx], t->vy2[s->idx], t->vz2[s->idx]);
	return (gjk_support_list(v, 3, dir));
}
