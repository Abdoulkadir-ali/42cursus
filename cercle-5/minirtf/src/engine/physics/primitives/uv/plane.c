/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:38:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	plane_uv(const t_plane *p, t_vec3 pt, float *u, float *v)
{
	t_vec3	t;
	t_vec3	b;
	t_vec3	d;

	if (fabsf(p->normal.y) < 0.9f)
		t = v3_norm(v3_cross(p->normal, v3(0, 1, 0)));
	else
		t = v3_norm(v3_cross(p->normal, v3(1, 0, 0)));
	b = v3_cross(p->normal, t);
	d = v3_sub(pt, p->point);
	*u = v3_dot(d, t);
	*v = v3_dot(d, b);
}
