/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:13:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_aabb	pyramid_bounds(const t_pyramid *p)
{
	t_aabb	b;
	t_vec3	c[5];
	float	s;
	int		i;

	s = p->side * 0.5f;
	c[0] = v3_add(p->base, v3_add(v3_mul(p->u, -s), v3_mul(p->v, -s)));
	c[1] = v3_add(p->base, v3_add(v3_mul(p->u,  s), v3_mul(p->v, -s)));
	c[2] = v3_add(p->base, v3_add(v3_mul(p->u,  s), v3_mul(p->v,  s)));
	c[3] = v3_add(p->base, v3_add(v3_mul(p->u, -s), v3_mul(p->v,  s)));
	c[4] = p->apex;
	b.min = c[0];
	b.max = c[0];
	i = 1;
	while (i < 5)
	{
		b.min.x = fminf(b.min.x, c[i].x);
		b.min.y = fminf(b.min.y, c[i].y);
		b.min.z = fminf(b.min.z, c[i].z);
		b.max.x = fmaxf(b.max.x, c[i].x);
		b.max.y = fmaxf(b.max.y, c[i].y);
		b.max.z = fmaxf(b.max.z, c[i].z);
		i++;
	}
	return (b);
}
