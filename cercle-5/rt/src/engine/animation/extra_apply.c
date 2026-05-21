/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 19:58:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

static void	mk_translate(t_mat4 o, t_vec3 d)
{
	skel_m4_identity(o);
	M4_AT(o, 0, 3) = d.x;
	M4_AT(o, 1, 3) = d.y;
	M4_AT(o, 2, 3) = d.z;
}

static void	mk_rotate(t_mat4 o, t_vec3 piv, const float r[9])
{
	skel_m4_identity(o);
	M4_AT(o, 0, 0) = r[0]; M4_AT(o, 0, 1) = r[1]; M4_AT(o, 0, 2) = r[2];
	M4_AT(o, 1, 0) = r[3]; M4_AT(o, 1, 1) = r[4]; M4_AT(o, 1, 2) = r[5];
	M4_AT(o, 2, 0) = r[6]; M4_AT(o, 2, 1) = r[7]; M4_AT(o, 2, 2) = r[8];
	M4_AT(o, 0, 3) = piv.x - (r[0] * piv.x + r[1] * piv.y + r[2] * piv.z);
	M4_AT(o, 1, 3) = piv.y - (r[3] * piv.x + r[4] * piv.y + r[5] * piv.z);
	M4_AT(o, 2, 3) = piv.z - (r[6] * piv.x + r[7] * piv.y + r[8] * piv.z);
}

static void	mk_scale(t_mat4 o, t_vec3 piv, float k)
{
	skel_m4_identity(o);
	M4_AT(o, 0, 0) = k;
	M4_AT(o, 1, 1) = k;
	M4_AT(o, 2, 2) = k;
	M4_AT(o, 0, 3) = (1.0f - k) * piv.x;
	M4_AT(o, 1, 3) = (1.0f - k) * piv.y;
	M4_AT(o, 2, 3) = (1.0f - k) * piv.z;
}

static void	apply_left(t_animator *a, const t_mat4 x)
{
	t_mat4	cur;
	t_mat4	out;

	if (!a->has_extra)
		skel_m4_identity(cur);
	else
		memcpy(cur, a->extra, sizeof(float) * 16);
	skel_m4_mul(x, cur, out);
	memcpy(a->extra, out, sizeof(float) * 16);
	a->has_extra = 1;
}

void	skel_animator_extra_apply(t_animator *a, int kind, t_vec3 piv,
		const void *data)
{
	t_mat4	x;

	if (!a || !data)
		return ;
	if (kind == 0)
		mk_translate(x, *(const t_vec3 *)data);
	else if (kind == 1)
		mk_rotate(x, piv, (const float *)data);
	else if (kind == 2)
		mk_scale(x, piv, *(const float *)data);
	else
		return ;
	apply_left(a, x);
}
