/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2026/03/06 20:07:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"


t_mat4	mat4_translation(t_vec3 v)
{
	t_mat4 m;

	m = mat4_identity();
	m.m[3][0] = v.x;
	m.m[3][1] = v.y;
	m.m[3][2] = v.z;
	return (m);
}

t_mat4	mat4_scaling(t_vec3 v)
{
	t_mat4 m;

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
	double	cx;
	double	sx;
	double	cy;
	double	sy;
	double	cz;
	double	sz;

	m = mat4_identity();
	ang = vec3(r.pitch, r.yaw, r.roll);
	ang = vec3_scale(ang, M_PI / 180.0);
	sx = sin(ang.x);
	cx = cos(ang.x);
	sy = sin(ang.y);
	cy = cos(ang.y);
	sz = sin(ang.z);
	cz = cos(ang.z);
	m.m[0][0] = cy * cz;
	m.m[0][1] = cy * sz;
	m.m[0][2] = -sy;
	m.m[1][0] = sx * sy * cz - cx * sz;
	m.m[1][1] = sx * sy * sz + cx * cz;
	m.m[1][2] = sx * cy;
	m.m[2][0] = cx * sy * cz + sx * sz;
	m.m[2][1] = cx * sy * sz - sx * cz;
	m.m[2][2] = cx * cy;
	return (m);
}

t_mat4	mat4_transform(t_transform t)
{
	t_mat4 m;

	m = mat4_mul(mat4_scaling(t.scale), mat4_rotation(t.rotation));
	m = mat4_mul(m, mat4_translation(t.pos));
	return (m);
}

t_mat4	mat4_inverse_transform(t_transform t)
{
	t_mat4 inv_t;
	t_mat4 inv_r;
	t_mat4 inv_s;
	t_mat4 r;
	t_mat4 m;
	int i;
	int j;

	r = mat4_rotation(t.rotation);
	inv_r = mat4_identity();
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			inv_r.m[i][j] = r.m[j][i];
	}
	inv_t = mat4_translation(vec3_scale(t.pos, -1.0));
	if (fabs(t.scale.x) < EPSILON)
		t.scale.x = 1.0;
	if (fabs(t.scale.y) < EPSILON)
		t.scale.y = 1.0;
	if (fabs(t.scale.z) < EPSILON)
		t.scale.z = 1.0;
	inv_s = mat4_scaling(vec3(1.0 / t.scale.x, 1.0 / t.scale.y, 1.0
				/ t.scale.z));
	m = mat4_mul(inv_t, inv_r);
	m = mat4_mul(m, inv_s);
	return (m);
}
