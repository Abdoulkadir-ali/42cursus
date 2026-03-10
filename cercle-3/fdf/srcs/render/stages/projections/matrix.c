/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:21:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

/**
 * @brief Convert a degree value to radians.
 * @param deg Angle in degrees.
 * @return Angle in radians.
 */
static float	to_radians(float deg)
{
	return (deg * (M_PI / 180.0f));
}

/**
 * @brief Build the projection matrix for parallel projection mode.
 * @param cam Camera providing projection tuning parameters.
 * @param aspect Aspect ratio used by the projection matrix.
 * @return Parallel projection matrix.
 */
static t_matrix4	get_parallel_matrix(t_camera *cam, float aspect)
{
	t_matrix4	mat;
	float		size;
	float		cotan;

	ft_memset(&mat, 0, sizeof(t_matrix4));
	size = 10.0f;
	mat.m[0][0] = 1.0f / (size * aspect);
	mat.m[1][1] = 1.0f / size;
	mat.m[2][2] = -2.0f / (10000.0f - 0.1f);
	if (fabs(cam->alpha - 90.0f) > 0.001f)
	{
		cotan = 1.0f / tanf(to_radians(cam->alpha));
		mat.m[0][2] = cotan;
		mat.m[1][2] = cotan;
		mat.m[0][3] = -(-500.0f * cotan);
		mat.m[1][3] = -(-500.0f * cotan);
	}
	mat.m[3][3] = 1.0f;
	return (mat);
}

/**
 * @brief Build the projection matrix for conic projection mode.
 * @param cam Camera providing field-of-view parameters.
 * @param aspect Aspect ratio used by the projection matrix.
 * @return Conic projection matrix.
 */
static t_matrix4	get_conic_matrix(t_camera *cam, float aspect)
{
	t_matrix4	mat;
	float		fov;
	float		tan_half_fov;

	ft_memset(&mat, 0, sizeof(t_matrix4));
	fov = cam->alpha;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 179.0f)
		fov = 179.0f;
	tan_half_fov = tanf(to_radians(fov) / 2.0f);
	mat.m[0][0] = 1.0f / (aspect * tan_half_fov);
	mat.m[1][1] = 1.0f / tan_half_fov;
	mat.m[2][2] = -1.0f;
	mat.m[2][3] = -2.0f * 0.1f;
	mat.m[3][2] = -1.0f;
	return (mat);
}

/**
 * @brief Select the active projection matrix for the current camera mode.
 * @param cam Camera providing the projection type and tuning values.
 * @param aspect Aspect ratio used by the projection matrix.
 * @return Projection matrix matching the active camera mode.
 */
t_matrix4	get_projection_matrix(t_camera *cam, float aspect)
{
	if (cam->projection == PROJ_PARALLEL)
		return (get_parallel_matrix(cam, aspect));
	return (get_conic_matrix(cam, aspect));
}
