/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeleton.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@local>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 18:30:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

/* Bone collider initialization is performed by the physics system during
 * scene baking; objects should not create or manage physics colliders. */

static t_mat4 quat_to_mat4(double x, double y, double z, double w)
{
    t_mat4 m = mat4_identity();
    double xx = x * x; double yy = y * y; double zz = z * z;
    double xy = x * y; double xz = x * z; double yz = y * z;
    double wx = w * x; double wy = w * y; double wz = w * z;

    m.m[0][0] = 1.0 - 2.0 * (yy + zz);
    m.m[0][1] = 2.0 * (xy + wz);
    m.m[0][2] = 2.0 * (xz - wy);

    m.m[1][0] = 2.0 * (xy - wz);
    m.m[1][1] = 1.0 - 2.0 * (xx + zz);
    m.m[1][2] = 2.0 * (yz + wx);

    m.m[2][0] = 2.0 * (xz + wy);
    m.m[2][1] = 2.0 * (yz - wx);
    m.m[2][2] = 1.0 - 2.0 * (xx + yy);

    return m;
}

/* (rest of original skeleton.c implementation moved here) */
