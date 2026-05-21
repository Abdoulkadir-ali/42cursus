/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:13:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_aabb	capsule_bounds(const t_capsule *c)
{
	t_aabb	b;
	t_vec3	p1;

	p1 = v3_add(c->base, v3_mul(c->axis, c->height));
	b.min.x = fminf(c->base.x, p1.x) - c->radius;
	b.min.y = fminf(c->base.y, p1.y) - c->radius;
	b.min.z = fminf(c->base.z, p1.z) - c->radius;
	b.max.x = fmaxf(c->base.x, p1.x) + c->radius;
	b.max.y = fmaxf(c->base.y, p1.y) + c->radius;
	b.max.z = fmaxf(c->base.z, p1.z) + c->radius;
	return (b);
}
