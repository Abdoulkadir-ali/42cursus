/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackhole.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:20:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

void	apply_blackhole_gravity(t_app *app, t_body *b, float dt)
{
	size_t	i;
	t_vec3	d;
	float	r2;
	float	a;
	float	rs;

	i = 0;
	while (i < app->scene.n_bhs)
	{
		rs = app->scene.bhs[i].rs;
		d = v3_sub(app->scene.bhs[i].pos, b->pos);
		r2 = v3_dot(d, d);
		if (r2 < rs * rs)
		{
			b->active = 0;
			b->vel = v3(0, 0, 0);
			return ;
		}
		if (r2 < 1e-6f)
			r2 = 1e-6f;
		a = app->scene.bhs[i].grav_strength * rs * rs * 80.0f / r2;
		b->vel = v3_add(b->vel, v3_mul(v3_norm(d), a * dt));
		i++;
	}
}
