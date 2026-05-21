/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:44:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	cylinder_uv(const t_cylinder *c, t_vec3 p, float *u, float *v)
{
	t_vec3	rel;
	t_vec3	t;
	t_vec3	b;
	t_vec3	uvh;

	rel = v3_sub(p, c->base);
	if (fabsf(c->axis.y) < 0.9f)
		t = v3_norm(v3_cross(c->axis, v3(0, 1, 0)));
	else
		t = v3_norm(v3_cross(c->axis, v3(1, 0, 0)));
	b = v3_cross(c->axis, t);
	uvh.x = v3_dot(rel, t);
	uvh.y = v3_dot(rel, b);
	uvh.z = v3_dot(rel, c->axis);
	*u = 0.5f + atan2f(uvh.y, uvh.x) / (2.0f * (float)M_PI);
	*v = uvh.z / c->height;
}
