/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

void	collide_planes(t_app *app, t_body *b)
{
	size_t	i;
	t_plane	*p;
	float	d;
	float	pen;
	float	vn;
	t_vec3	tv;
	float	tvm;
	float	mu;

	i = 0;
	while (i < app->scene.n_planes)
	{
		p = &app->scene.planes[i].u.pln;
		d = v3_dot(v3_sub(b->pos, p->point), p->normal);
		pen = b->radius_cache - d;
		if (pen > 0.0f)
		{
			b->pos = v3_add(b->pos, v3_mul(p->normal, pen));
			vn = v3_dot(b->vel, p->normal);
			if (vn < 0.0f)
			{
				b->vel = v3_sub(b->vel, v3_mul(p->normal,
						(1.0f + b->restitution) * vn));
				tv = v3_sub(b->vel, v3_mul(p->normal,
						v3_dot(b->vel, p->normal)));
				tvm = v3_len(tv);
				if (tvm > 1e-4f)
				{
					mu = app->set.physics.friction;
					if (mu > 1.0f)
						mu = 1.0f;
					b->vel = v3_sub(b->vel, v3_mul(tv, mu));
				}
				if (app->set.rt.collision_heat && b->inv_mass > 0.0f)
					b->temperature += 0.5f * (1.0f - b->restitution
						* b->restitution) * (vn * vn) * b->inv_mass
					/ 0.05f;
			}
		}
		i++;
	}
}
