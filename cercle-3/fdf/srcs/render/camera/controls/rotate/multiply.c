/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 05:18:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:09:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	mat_mul(const t_vec3d a[3], const t_vec3d b[3], t_vec3d out[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out[i].x = a[i].x * b[0].x + a[i].y * b[1].x + a[i].z * b[2].x;
		out[i].y = a[i].x * b[0].y + a[i].y * b[1].y + a[i].z * b[2].y;
		out[i].z = a[i].x * b[0].z + a[i].y * b[1].z + a[i].z * b[2].z;
		++i;
	}
}

void	mat_vec_mul(const t_vec3d m[3], t_vec3d v, t_vec3d *result)
{
	t_vec3d	tmp;

	*result = m[0];
	vec3d_multiply_scalar(result, v.x);
	tmp = m[1];
	vec3d_multiply_scalar(&tmp, v.y);
	vec3d_add(result, tmp);
	tmp = m[2];
	vec3d_multiply_scalar(&tmp, v.z);
	vec3d_add(result, tmp);
}

void	compose_rotation_matrix(t_camera *cam, t_rot_ctx *ctx)
{
	t_vec3d	rx[3];
	t_vec3d	ry[3];
	t_vec3d	rz[3];
	t_vec3d	tmp[3];
	t_vec3d	out[3];

	build_rotation_matrices(rx, ry, rz, ctx);
	
	/* Desired Order: Rx * Ry * Rz * P */
	/* 1. tmp = Ry * Rz */
	mat_mul(ry, rz, tmp);
	/* 2. out = Rx * tmp = Rx * Ry * Rz */
	mat_mul(rx, tmp, out);
	
	cam->rotation_matrix[0] = out[0];
	cam->rotation_matrix[1] = out[1];
	cam->rotation_matrix[2] = out[2];
}
