/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:06:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 18:08:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
/* near_sphere_t and cylinder_body_t are now static inline in raytracing.h */

static void	set_uv_tan(t_capsule *cp, t_hit *h, t_cap_calc *c, t_vec3 lo)
{
	t_vec3	basis[2];

	vec3_orthonormal_basis(cp->axis, &basis[0], &basis[1]);
	h->u = (atan2(vec3_dot(lo, basis[1]), vec3_dot(lo, basis[0])) + M_PI)
		/ (6.28318530718);
	h->v = (vec3_dot(lo, cp->axis) / cp->half_height + 1.0) * 0.5;
	if (c->type.i != 0)
		h->v = (vec3_dot(lo, cp->axis) + 1.0) * 0.5;
	h->tangent = vec3_norm(vec3_cross(cp->axis, h->normal));
	h->bitangent = cp->axis;
	if (c->type.i != 0)
		h->bitangent = vec3_norm(vec3_cross(h->normal, h->tangent));
}

void	update_capsule_hit(t_capsule *cp, t_hit *h, t_cap_calc *c,
			const t_ray *r)
{
	t_vec3	norm;
	t_vec3	lo;

	if (c->type.i == 0)
		norm = vec3_norm(vec3_sub(vec3_sub(h->point, cp->transform.pos),
					vec3_scale(cp->axis, vec3_dot(vec3_sub(h->point,
								cp->transform.pos), cp->axis))));
	else
		norm = vec3_norm(vec3_sub(h->point, c->p[c->type.i - 1]));
	h->back_face = vec3_dot(r->direction, norm) > 0;
	if (h->back_face)
		norm = vec3_scale(norm, -1.0);
	h->normal = norm;
	lo = vec3_sub(h->point, cp->transform.pos);
	if (c->type.i != 0)
		lo = vec3_norm(vec3_sub(h->point, c->p[c->type.i - 1]));
	set_uv_tan(cp, h, c, lo);
}
