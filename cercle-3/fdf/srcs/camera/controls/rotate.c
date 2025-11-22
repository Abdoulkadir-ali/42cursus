/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:10:37 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 03:10:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	init_rot_ctx(t_rot_ctx *c, t_camera *cam)
{
    if (!c || !cam)
        return ;
    c->rot = create_vec3d(cam->rotation.x, cam->rotation.y, cam->rotation.z);
    c->cosv = create_vec3d(cos(c->rot.x), cos(c->rot.y), cos(c->rot.z));
    c->sinv = create_vec3d(sin(c->rot.x), sin(c->rot.y), sin(c->rot.z));
}

static void	build_rx(t_vec3d Rx[3], double cx, double sx)
{
    Rx[0] = create_vec3d(1.0, 0.0, 0.0);
    Rx[1] = create_vec3d(0.0, cx, -sx);
    Rx[2] = create_vec3d(0.0, sx, cx);
}

static void	build_ry(t_vec3d Ry[3], double cy, double sy)
{
    Ry[0] = create_vec3d(cy, 0.0, sy);
    Ry[1] = create_vec3d(0.0, 1.0, 0.0);
    Ry[2] = create_vec3d(-sy, 0.0, cy);
}

static void	build_rz(t_vec3d Rz[3], double cz, double sz)
{
    Rz[0] = create_vec3d(cz, -sz, 0.0);
    Rz[1] = create_vec3d(sz, cz, 0.0);
    Rz[2] = create_vec3d(0.0, 0.0, 1.0);
}


static void	mat_mul(const t_vec3d A[3], const t_vec3d B[3], t_vec3d out[3])
{
    int i;

    i = 0;
    while (i < 3)
    {
        out[i].x = A[i].x * B[0].x + A[i].y * B[1].x + A[i].z * B[2].x;
        out[i].y = A[i].x * B[0].y + A[i].y * B[1].y + A[i].z * B[2].y;
        out[i].z = A[i].x * B[0].z + A[i].y * B[1].z + A[i].z * B[2].z;
        ++i;
    }
}
static t_vec3d	mat_vec_mul(const t_vec3d M[3], t_vec3d v)
{
    t_vec3d r;
    t_vec3d tmp;

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

static void	compose_rotation_matrix(t_camera *cam, t_rot_ctx *ctx)
{
    t_vec3d Rx[3];
    t_vec3d Ry[3];
    t_vec3d Rz[3];
    t_vec3d tmp[3];
    t_vec3d out[3];

    build_rx(Rx, ctx->cosv.x, ctx->sinv.x);
    build_ry(Ry, ctx->cosv.y, ctx->sinv.y);
    build_rz(Rz, ctx->cosv.z, ctx->sinv.z);
    mat_mul(Ry, Rx, tmp);
    mat_mul(Rz, tmp, out);
    cam->rotation_matrix[0] = out[0];
    cam->rotation_matrix[1] = out[1];
    cam->rotation_matrix[2] = out[2];
}

void	update_rotation_matrix(t_camera *cam)
{
    t_rot_ctx ctx;

    if (!cam)
        return ;
    init_rot_ctx(&ctx, cam);
    compose_rotation_matrix(cam, &ctx);
}

t_vec3d	apply_rotation_with_matrix(t_vec3d v, t_camera *cam)
{
    if (!cam)
        return (v);
    return (mat_vec_mul(cam->rotation_matrix, v));
}

t_vec3d	apply_rotation_centered_with_matrix(t_vec3d v, t_camera *cam)
{
    t_vec3d centered;
    t_vec3d rotated;

    centered = v;
    vec3d_sub(&centered, cam->grid_center);
    rotated = apply_rotation_with_matrix(centered, cam);
    vec3d_add(&rotated, cam->grid_center);
    return (rotated);
}
