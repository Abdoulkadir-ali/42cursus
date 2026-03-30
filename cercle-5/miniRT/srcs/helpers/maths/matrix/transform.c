/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:07:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_mat4	mat4_translation(t_vec3 v)
{
	t_mat4	m;

	m = mat4_identity();
	m.m[3][0] = v.x;
	m.m[3][1] = v.y;
	m.m[3][2] = v.z;
	return (m);
}

t_mat4	mat4_scaling(t_vec3 v)
{
	t_mat4	m;

	m = mat4_identity();
	m.m[0][0] = v.x;
	m.m[1][1] = v.y;
	m.m[2][2] = v.z;
	return (m);
}

t_mat4	mat4_rotation(t_rotator r)
{
	t_mat4	m;
	t_vec3	ang;
	t_vec3	c;
	t_vec3	s;

	m = mat4_identity();
	ang = vec3(r.pitch, r.yaw, r.roll);
	ang = vec3_scale(ang, M_PI / 180.0);
	c = vec3(cos(ang.x), cos(ang.y), cos(ang.z));
	s = vec3(sin(ang.x), sin(ang.y), sin(ang.z));
	m.m[0][0] = c.y * c.z;
	m.m[0][1] = c.y * s.z;
	m.m[0][2] = -s.y;
	m.m[1][0] = s.x * s.y * c.z - c.x * s.z;
	m.m[1][1] = s.x * s.y * s.z + c.x * c.z;
	m.m[1][2] = s.x * c.y;
	m.m[2][0] = c.x * s.y * c.z + s.x * s.z;
	m.m[2][1] = c.x * s.y * s.z - s.x * c.z;
	m.m[2][2] = c.x * c.y;
	return (m);
}

t_mat4	mat4_transform(t_transform t)
{
	t_mat4	m;

	m = mat4_mul(mat4_scaling(t.scale), mat4_rotation(t.rotation));
	m = mat4_mul(m, mat4_translation(t.pos));
	return (m);
}
