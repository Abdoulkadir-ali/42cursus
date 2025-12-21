/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:10:37 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:09:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_vec3d	mat_vec_mul(const t_vec3d M[3], t_vec3d v)
{
	t_vec3d	r;
	t_vec3d	tmp;

	r = M[0];
	vec3d_multiply_scalar(&r, v.x);
	tmp = M[1];
	vec3d_multiply_scalar(&tmp, v.y);
	vec3d_add(&r, tmp);
	tmp = M[2];
	vec3d_multiply_scalar(&tmp, v.z);
	vec3d_add(&r, tmp);
	return (r);
}

t_vec3d	apply_rotation_with_matrix(t_vec3d v, t_camera *cam)
{
	if (!cam)
		return (v);
	return (mat_vec_mul(cam->rotation_matrix, v));
}

t_vec3d	apply_rotation_centered_with_matrix(t_vec3d v, t_camera *cam)
{
	t_vec3d	centered;
	t_vec3d	rotated;

	centered = v;
	vec3d_sub(&centered, cam->grid_center);
	rotated = apply_rotation_with_matrix(centered, cam);

	return (rotated);
}
