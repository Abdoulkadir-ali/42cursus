/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 05:18:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:09:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/**
 * @brief Build the rotation matrix around the X axis.
 * @param rx Output 3x3 matrix rows for the X rotation.
 * @param cx Cosine of the X rotation angle.
 * @param sx Sine of the X rotation angle.
 */
static void	build_rx(t_vec3d rx[3], double cx, double sx)
{
	rx[0] = create_vec3d(1.0, 0.0, 0.0);
	rx[1] = create_vec3d(0.0, cx, -sx);
	rx[2] = create_vec3d(0.0, sx, cx);
}

/**
 * @brief Build the rotation matrix around the Y axis.
 * @param ry Output 3x3 matrix rows for the Y rotation.
 * @param cy Cosine of the Y rotation angle.
 * @param sy Sine of the Y rotation angle.
 */
static void	build_ry(t_vec3d ry[3], double cy, double sy)
{
	ry[0] = create_vec3d(cy, 0.0, sy);
	ry[1] = create_vec3d(0.0, 1.0, 0.0);
	ry[2] = create_vec3d(-sy, 0.0, cy);
}

/**
 * @brief Build the rotation matrix around the Z axis.
 * @param rz Output 3x3 matrix rows for the Z rotation.
 * @param cz Cosine of the Z rotation angle.
 * @param sz Sine of the Z rotation angle.
 */
static void	build_rz(t_vec3d rz[3], double cz, double sz)
{
	rz[0] = create_vec3d(cz, -sz, 0.0);
	rz[1] = create_vec3d(sz, cz, 0.0);
	rz[2] = create_vec3d(0.0, 0.0, 1.0);
}

/**
 * @brief Build the three axis rotation matrices from a prepared context.
 * @param rx Output matrix for the X axis rotation.
 * @param ry Output matrix for the Y axis rotation.
 * @param rz Output matrix for the Z axis rotation.
 * @param ctx Precomputed trigonometric rotation context.
 */
void	build_rotation_matrices(t_vec3d rx[3], t_vec3d ry[3], t_vec3d rz[3],
		t_rot_ctx *ctx)
{
	build_rx(rx, ctx->cos.x, ctx->sin.x);
	build_ry(ry, ctx->cos.y, ctx->sin.y);
	build_rz(rz, ctx->cos.z, ctx->sin.z);
}
