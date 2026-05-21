/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:13:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_aabb	cylinder_bounds(const t_cylinder *c)
{
	t_aabb		b;
	t_cylinder_bounds	cb;

	cb.p0 = c->base;
	cb.p1 = v3_add(c->base, v3_mul(c->axis, c->height));
	cb.a = c->axis;
	cb.e.x = c->radius * sqrtf(fmaxf(0.0f, 1.0f - cb.a.x * cb.a.x));
	cb.e.y = c->radius * sqrtf(fmaxf(0.0f, 1.0f - cb.a.y * cb.a.y));
	cb.e.z = c->radius * sqrtf(fmaxf(0.0f, 1.0f - cb.a.z * cb.a.z));

	cb.lo = v3(fminf(cb.p0.x, cb.p1.x), fminf(cb.p0.y, cb.p1.y),
		fminf(cb.p0.z, cb.p1.z));
	cb.hi = v3(fmaxf(cb.p0.x, cb.p1.x), fmaxf(cb.p0.y, cb.p1.y),
		fmaxf(cb.p0.z, cb.p1.z));
	b.min = v3_sub(cb.lo, cb.e);
	b.max = v3_add(cb.hi, cb.e);
	return (b);
}
