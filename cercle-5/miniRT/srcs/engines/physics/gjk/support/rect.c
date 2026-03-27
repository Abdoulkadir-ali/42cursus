/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a rectangle.
 * Computes world-space corners on-the-fly from SoA basis (ax-tx) and extents.
 */
t_vec3	gjk_support_rect(const t_gjk_shape *s, t_vec3 dir)
{
	t_primitive_array	*p;
	t_vec3				v[4];
	t_vec3				normal;
	t_vec3				tangent;
	t_vec3				bitangent;
	t_vec3				pos;

	p = &s->scene->primitives;
	pos = vec3(p->px[s->idx], p->py[s->idx], p->pz[s->idx]);
	normal = vec3(p->ax[s->idx], p->ay[s->idx], p->az[s->idx]);
	tangent = vec3(p->tx[s->idx], p->ty[s->idx], p->tz[s->idx]);
	bitangent = vec3_norm(vec3_cross(normal, tangent));
	v[0] = vec3_add(vec3_add(pos, vec3_scale(tangent, p->ex[s->idx])),
			vec3_scale(bitangent, p->ey[s->idx]));
	v[1] = vec3_add(vec3_add(pos, vec3_scale(tangent, -p->ex[s->idx])),
			vec3_scale(bitangent, p->ey[s->idx]));
	v[2] = vec3_add(vec3_add(pos, vec3_scale(tangent, -p->ex[s->idx])),
			vec3_scale(bitangent, -p->ey[s->idx]));
	v[3] = vec3_add(vec3_add(pos, vec3_scale(tangent, p->ex[s->idx])),
			vec3_scale(bitangent, -p->ey[s->idx]));
	return (gjk_support_list(v, 4, dir));
}
