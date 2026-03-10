/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:21:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

/**
 * @brief Recenter and z-scale a point before matrix transformation.
 * @param p Source point in map space.
 * @param cam Camera providing grid-center and z-scale data.
 * @return Adjusted vector ready for matrix multiplication.
 */
static t_vec3d	apply_pre_adjustments(t_point p, t_camera *cam)
{
	t_vec3d	effective_center_scaled;
	t_vec3d	scaled_pos;
	t_vec3d	v;

	effective_center_scaled = cam->grid_center;
	effective_center_scaled.z *= cam->z_scale;
	scaled_pos = p.pos;
	scaled_pos.z *= cam->z_scale;
	v.x = p.pos.x - effective_center_scaled.x;
	v.y = p.pos.y - effective_center_scaled.y;
	v.z = scaled_pos.z - effective_center_scaled.z;
	return (v);
}

/**
 * @brief Apply the cached camera transform matrix to an adjusted vector.
 * @param v Adjusted input vector.
 * @param cam Camera holding the cached transform matrix.
 * @return Matrix multiplication result with homogeneous divide applied.
 */
static t_matrix_result	apply_matrix_transform(t_vec3d v, t_camera *cam)
{
	t_matrix4		*m;
	float			inv_w;
	t_matrix_result	res;

	m = &cam->transform_matrix;
	res.x = (float)v.x * m->m[0][0] + (float)v.y * m->m[0][1] + (float)v.z
		* m->m[0][2] + m->m[0][3];
	res.y = (float)v.x * m->m[1][0] + (float)v.y * m->m[1][1] + (float)v.z
		* m->m[1][2] + m->m[1][3];
	res.w = (float)v.x * m->m[3][0] + (float)v.y * m->m[3][1] + (float)v.z
		* m->m[3][2] + m->m[3][3];
	if (res.w != 0.0f)
	{
		inv_w = 1.0f / res.w;
		res.x *= inv_w;
		res.y *= inv_w;
	}
	return (res);
}

/**
 * @brief Apply screen offset and depth reconstruction after matrix projection.
 * @param res Point structure receiving final screen-space coordinates.
 * @param mres Intermediate matrix multiplication result.
 * @param cam Camera providing offset and rotation data.
 * @param v Adjusted pre-transform vector used for depth reconstruction.
 * @return Final projected point.
 */
static t_point	apply_post_offset(t_point res, t_matrix_result mres,
		t_camera *cam, t_vec3d v)
{
	res.pos.x = mres.x + cam->offset.x;
	res.pos.y = mres.y + cam->offset.y;
	res.pos.z = v.x * cam->rotation_matrix[2].x + v.y
		* cam->rotation_matrix[2].y + v.z * cam->rotation_matrix[2].z
		- cam->view_dist;
	return (res);
}

/**
 * @brief Transform one point from map space into screen space.
 * @param p Source point to transform.
 * @param cam Camera providing the cached transform state.
 * @return Projected point with updated position and preserved color.
 */
t_point	apply_transform(t_point p, t_camera *cam)
{
	t_vec3d			v;
	t_point			res;
	t_matrix_result	mres;

	v = apply_pre_adjustments(p, cam);
	mres = apply_matrix_transform(v, cam);
	res = p;
	res = apply_post_offset(res, mres, cam, v);
	return (res);
}
