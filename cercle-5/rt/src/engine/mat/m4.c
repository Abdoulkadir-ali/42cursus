/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m4.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 14:59:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

void	skel_m4_identity(t_mat4 m)
{
	memset(m, 0, sizeof(float) * 16);
	M4_AT(m, 0, 0) = 1.0f;
	M4_AT(m, 1, 1) = 1.0f;
	M4_AT(m, 2, 2) = 1.0f;
	M4_AT(m, 3, 3) = 1.0f;
}

void	skel_m4_mul(const t_mat4 a, const t_mat4 b, t_mat4 o)
{
	t_mat4	r;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			M4_AT(r, j, i) = M4_AT(a, j, 0) * M4_AT(b, 0, i) + M4_AT(a, j, 1)
				* M4_AT(b, 1, i) + M4_AT(a, j, 2) * M4_AT(b, 2, i) + M4_AT(a, j,
					3) * M4_AT(b, 3, i);
			j++;
		}
		i++;
	}
	memcpy(o, r, sizeof(r));
}

void	skel_m4_from_trs(const t_vec3 *t, const t_vec4 *q, const t_vec3 *s,
		t_mat4 m)
{
	const float	v[9] = {q->x * q->x, q->y * q->y, q->z * q->z, q->x * q->y, q->x
			* q->z, q->y * q->z, q->w * q->x, q->w * q->y, q->w * q->z};

	M4_AT(m, 0, 0) = (1.0f - 2.0f * (v[1] + v[2])) * s->x;
	M4_AT(m, 1, 0) = (2.0f * (v[3] + v[8])) * s->x;
	M4_AT(m, 2, 0) = (2.0f * (v[4] - v[7])) * s->x;
	M4_AT(m, 3, 0) = 0.0f;
	M4_AT(m, 0, 1) = (2.0f * (v[3] - v[8])) * s->y;
	M4_AT(m, 1, 1) = (1.0f - 2.0f * (v[0] + v[2])) * s->y;
	M4_AT(m, 2, 1) = (2.0f * (v[5] + v[6])) * s->y;
	M4_AT(m, 3, 1) = 0.0f;
	M4_AT(m, 0, 2) = (2.0f * (v[4] + v[7])) * s->z;
	M4_AT(m, 1, 2) = (2.0f * (v[5] - v[6])) * s->z;
	M4_AT(m, 2, 2) = (1.0f - 2.0f * (v[0] + v[1])) * s->z;
	M4_AT(m, 3, 2) = 0.0f;
	M4_AT(m, 0, 3) = t->x;
	M4_AT(m, 1, 3) = t->y;
	M4_AT(m, 2, 3) = t->z;
	M4_AT(m, 3, 3) = 1.0f;
}

t_vec3	skel_m4_xform_pos(const t_mat4 m, t_vec3 p)
{
	t_vec3	o;

	o.x = M4_AT(m, 0, 0) * p.x + M4_AT(m, 0, 1) * p.y + M4_AT(m, 0, 2) * p.z
		+ M4_AT(m, 0, 3);
	o.y = M4_AT(m, 1, 0) * p.x + M4_AT(m, 1, 1) * p.y + M4_AT(m, 1, 2) * p.z
		+ M4_AT(m, 1, 3);
	o.z = M4_AT(m, 2, 0) * p.x + M4_AT(m, 2, 1) * p.y + M4_AT(m, 2, 2) * p.z
		+ M4_AT(m, 2, 3);
	return (o);
}
