/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_matrix_builders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 05:18:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:21:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	build_rx(t_vec3d rx[3], double cx, double sx)
{
	rx[0] = create_vec3d(1.0, 0.0, 0.0);
	rx[1] = create_vec3d(0.0, cx, -sx);
	rx[2] = create_vec3d(0.0, sx, cx);
}

static void	build_ry(t_vec3d ry[3], double cy, double sy)
{
	ry[0] = create_vec3d(cy, 0.0, sy);
	ry[1] = create_vec3d(0.0, 1.0, 0.0);
	ry[2] = create_vec3d(-sy, 0.0, cy);
}

static void	build_rz(t_vec3d rz[3], double cz, double sz)
{
	rz[0] = create_vec3d(cz, -sz, 0.0);
	rz[1] = create_vec3d(sz, cz, 0.0);
	rz[2] = create_vec3d(0.0, 0.0, 1.0);
}

void	build_rotation_matrices(t_vec3d rx[3], t_vec3d ry[3], t_vec3d rz[3],
		t_rot_ctx *ctx)
{
	build_rx(rx, ctx->cosv.x, ctx->sinv.x);
	build_ry(ry, ctx->cosv.y, ctx->sinv.y);
	build_rz(rz, ctx->cosv.z, ctx->sinv.z);
}
