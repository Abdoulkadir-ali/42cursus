/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 11:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	t_mat4	res;
	int		i;
	int		j;
	int		k;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			res.m[i][j] = 0;
			for (k = 0; k < 4; k++)
				res.m[i][j] += a.m[i][k] * b.m[k][j];
		}
	}
	return (res);
}

t_mat4	mat4_identity(void)
{
	t_mat4	res;
	int		i;
	int		j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			res.m[i][j] = (i == j);
	return (res);
}

t_vec3	mat4_mul_vec3(t_mat4 m, t_vec3 v)
{
	t_vec3	res;

	res.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w
		* m.m[3][0];
	res.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w
		* m.m[3][1];
	res.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w
		* m.m[3][2];
	res.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w
		* m.m[3][3];
	return (res);
}

t_mat4	mat4_scale_inplace(t_mat4 m, double s)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m.m[i][j] *= s;
	return (m);
}

t_mat4	mat4_add(t_mat4 a, t_mat4 b)
{
	t_mat4	res;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			res.m[i][j] = a.m[i][j] + b.m[i][j];
	return (res);
}

t_mat4	mat4_translation(t_vec3 v)
{
	t_mat4	m = mat4_identity();
	m.m[3][0] = v.x;
	m.m[3][1] = v.y;
	m.m[3][2] = v.z;
	return (m);
}

t_mat4	mat4_scaling(t_vec3 v)
{
	t_mat4	m = mat4_identity();
	m.m[0][0] = v.x;
	m.m[1][1] = v.y;
	m.m[2][2] = v.z;
	return (m);
}

t_mat4	mat4_rotation(t_rotator r)
{
	t_mat4 m = mat4_identity();
	double p = r.pitch * M_PI / 180.0;
	double y = r.yaw * M_PI / 180.0;
	double rl = r.roll * M_PI / 180.0;
	double cp = cos(p), sp = sin(p);
	double cy = cos(y), sy = sin(y);
	double cr = cos(rl), sr = sin(rl);

	m.m[0][0] = cy * cr;
	m.m[0][1] = cy * sr;
	m.m[0][2] = -sy;
	m.m[1][0] = sp * sy * cr - cp * sr;
	m.m[1][1] = sp * sy * sr + cp * cr;
	m.m[1][2] = sp * cy;
	m.m[2][0] = cp * sy * cr + sp * sr;
	m.m[2][1] = cp * sy * sr - sp * cr;
	m.m[2][2] = cp * cy;
	return (m);
}

t_mat4	mat4_transform(t_transform t)
{
	t_mat4 m;
	m = mat4_mul(mat4_scaling(t.scale), mat4_rotation(t.rotation));
	m = mat4_mul(m, mat4_translation(t.pos));
	return (m);
}

t_vec3	mat4_mul_pos(t_mat4 m, t_vec3 v)
{
	t_vec3 res;
	double w;
	res.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	res.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	res.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	res.w = 1.0;
	w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	if (w != 0 && w != 1.0)
	{
		res.x /= w; res.y /= w; res.z /= w;
	}
	return (res);
}
