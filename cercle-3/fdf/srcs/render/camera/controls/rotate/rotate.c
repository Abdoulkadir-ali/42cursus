/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:10:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:09:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/**
 * @brief Multiply a cached 3x3 matrix by one vector and return the result.
 * @param M Matrix to apply.
 * @param v Input vector.
 * @return Rotated vector.
 */
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

/**
 * @brief Rotate a vector with the camera cached rotation matrix.
 * @param v Vector to rotate.
 * @param cam Camera holding the rotation matrix.
 * @return Rotated vector, or the input vector if `cam` is `NULL`.
 */
t_vec3d	apply_rotation_with_matrix(t_vec3d v, t_camera *cam)
{
	if (!cam)
		return (v);
	return (mat_vec_mul(cam->rotation_matrix, v));
}
