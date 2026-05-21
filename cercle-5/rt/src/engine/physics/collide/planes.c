/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:41:34 by abdoali          ###   ########.fr       */
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

static void	planes_chunk(void *data)
{
	t_planes_job	*j;
	int				i;

	j = (t_planes_job *)data;
	i = j->start;
	while (i < j->end)
	{
		if (j->app->phys.bodies[i].active)
			collide_planes(j->app, &j->app->phys.bodies[i]);
		i++;
	}
}

void	collide_planes_all(t_app *app)
{
	int	n;
	int	w;
	int	chunk;
	int	i;

	n = app->phys.n;
	w = app->pool.tpool.n_workers;
	if (n < 32 || w <= 1)
	{
		i = 0;
		while (i < n)
		{
			if (app->phys.bodies[i].active)
				collide_planes(app, &app->phys.bodies[i]);
			i++;
		}
		return ;
	}
	chunk = (n + w - 1) / w;
	i = 0;
	while (i < w)
	{
		app->phys.planes_jobs[i].app = app;
		app->phys.planes_jobs[i].start = i * chunk;
		app->phys.planes_jobs[i].end = i * chunk + chunk;
		if (app->phys.planes_jobs[i].end > n)
			app->phys.planes_jobs[i].end = n;
		if (app->phys.planes_jobs[i].start < n)
			tpool_submit(&app->pool.tpool, planes_chunk, &app->phys.planes_jobs[i]);
		i++;
	}
	tpool_wait(&app->pool.tpool);
}
