/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:20:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

void	integrate(t_app *app, float dt)
{
	int		i;
	t_body	*b;
	float	cool_k;
	float	v2;

	cool_k = 0.4f;
	i = 0;
	while (i < app->phys.n)
	{
		b = &app->phys.bodies[i];
		if (b->active)
		{
			if (b->inv_mass > 0.0f && b->sleep_frames < 30)
			{
				b->vel = v3_add(b->vel, v3_mul(app->scene.gravity, dt));
				apply_blackhole_gravity(app, b, dt);
				if (!b->active)
				{
					i++;
					continue ;
				}
				b->acc = app->scene.gravity;
				b->pos = v3_add(b->pos, v3_mul(b->vel, dt));
				v2 = v3_dot(b->vel, b->vel);
				if (v2 < 1e-4f)
					b->sleep_frames++;
				else
					b->sleep_frames = 0;
			}
			b->temperature -= cool_k * (b->temperature - b->temp_ambient) * dt;
			if (b->temperature < b->temp_ambient)
				b->temperature = b->temp_ambient;
		}
		i++;
	}
}
