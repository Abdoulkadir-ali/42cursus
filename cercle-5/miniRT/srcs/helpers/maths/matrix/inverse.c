/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:52:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 15:52:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static t_mat4	mat4_transpose_3x3(t_mat4 r)
{
	t_mat4	res;
	int		i;
	int		j;

	res = mat4_identity();
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			res.m[i][j] = r.m[j][i];
	}
	return (res);
}

t_mat4	mat4_inverse_transform(t_transform t)
{
	t_mat4	inv_t;
	t_mat4	inv_r;
	t_mat4	inv_s;
	t_mat4	m;

	inv_r = mat4_transpose_3x3(mat4_rotation(t.rotation));
	inv_t = mat4_translation(vec3_scale(t.pos, -1.0));
	if (fabs(t.scale.x) < 1e-6)
		t.scale.x = 1.0;
	if (fabs(t.scale.y) < 1e-6)
		t.scale.y = 1.0;
	if (fabs(t.scale.z) < 1e-6)
		t.scale.z = 1.0;
	inv_s = mat4_scaling(vec3(1.0 / t.scale.x, 1.0 / t.scale.y, 1.0
				/ t.scale.z));
	m = mat4_mul(inv_t, inv_r);
	m = mat4_mul(m, inv_s);
	return (m);
}
