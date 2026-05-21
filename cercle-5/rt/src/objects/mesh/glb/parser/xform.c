/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xform.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 01:25:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

void	glb_make_rot(float m[9], t_vec3 deg)
{
	t_vec3	c;
	t_vec3	s;

	c.x = cosf(deg.x * 0.01745329252f);
	s.x = sinf(deg.x * 0.01745329252f);
	c.y = cosf(deg.y * 0.01745329252f);
	s.y = sinf(deg.y * 0.01745329252f);
	c.z = cosf(deg.z * 0.01745329252f);
	s.z = sinf(deg.z * 0.01745329252f);
	m[0] = c.z * c.y;
	m[1] = c.z * s.y * s.x - s.z * c.x;
	m[2] = c.z * s.y * c.x + s.z * s.x;
	m[3] = s.z * c.y;
	m[4] = s.z * s.y * s.x + c.z * c.x;
	m[5] = s.z * s.y * c.x - c.z * s.x;
	m[6] = -s.y;
	m[7] = c.y * s.x;
	m[8] = c.y * c.x;
}

t_vec3	glb_apply_outer(const t_glb *g, t_vec3 p)
{
	t_vec3	q;
	t_vec3	o;

	q = v3_mul(p, g->scale);
	o.x = g->rot[0] * q.x + g->rot[1] * q.y + g->rot[2] * q.z + g->origin.x;
	o.y = g->rot[3] * q.x + g->rot[4] * q.y + g->rot[5] * q.z + g->origin.y;
	o.z = g->rot[6] * q.x + g->rot[7] * q.y + g->rot[8] * q.z + g->origin.z;
	return (o);
}
