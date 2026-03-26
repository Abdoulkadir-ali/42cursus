/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	mat3_mul_vec3(t_mat3 m, t_vec3 v)
{
	t_vec3	r;

	r.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	r.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	r.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
	r.w = 0.0;
	return (r);
}

t_mat3	mat3_mul(t_mat3 a, t_mat3 b)
{
	t_mat3	r;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			r.m[i][j] = a.m[i][0] * b.m[0][j]
				+ a.m[i][1] * b.m[1][j]
				+ a.m[i][2] * b.m[2][j];
			j++;
		}
		i++;
	}
	return (r);
}

t_mat3	mat3_transpose(t_mat3 m)
{
	t_mat3	r;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			r.m[i][j] = m.m[j][i];
			j++;
		}
		i++;
	}
	return (r);
}

t_mat3	mat3_inv(t_mat3 m)
{
	t_mat3	r;
	double	det;
	double	inv_det;

	det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1])
		- m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0])
		+ m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
	if (fabs(det) < 1e-12)
		return (m);
	inv_det = 1.0 / det;
	r.m[0][0] = (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) * inv_det;
	r.m[0][1] = (m.m[0][2] * m.m[2][1] - m.m[0][1] * m.m[2][2]) * inv_det;
	r.m[0][2] = (m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1]) * inv_det;
	r.m[1][0] = (m.m[1][2] * m.m[2][0] - m.m[1][0] * m.m[2][2]) * inv_det;
	r.m[1][1] = (m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0]) * inv_det;
	r.m[1][2] = (m.m[0][2] * m.m[1][0] - m.m[0][0] * m.m[1][2]) * inv_det;
	r.m[2][0] = (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]) * inv_det;
	r.m[2][1] = (m.m[0][1] * m.m[2][0] - m.m[0][0] * m.m[2][1]) * inv_det;
	r.m[2][2] = (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]) * inv_det;
	return (r);
}

t_mat3	mat3_diag(t_vec3 v)
{
	t_mat3	r;

	memset(&r, 0, sizeof(t_mat3));
	r.m[0][0] = v.x;
	r.m[1][1] = v.y;
	r.m[2][2] = v.z;
	return (r);
}
