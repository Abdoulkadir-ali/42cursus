/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:41:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

static void	integrate_body(t_app *app, t_body *b, float dt)
{
	float	cool_k;
	float	v2;

	cool_k = 0.4f;
	if (!b->active)
		return ;
	if (b->inv_mass > 0.0f && b->sleep_frames < 30)
	{
		b->vel = v3_add(b->vel, v3_mul(app->scene.gravity, dt));
		apply_blackhole_gravity(app, b, dt);
		if (!b->active)
			return ;
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

static void	integrate_chunk(void *data)
{
	t_integrate_job	*j;
	int				i;

	j = (t_integrate_job *)data;
	i = j->start;
	while (i < j->end)
		integrate_body(j->app, &j->app->phys.bodies[i++], j->dt);
}

static void	integrate_parallel(t_app *app, float dt)
{
	int	w;
	int	chunk;
	int	i;

	w = app->pool.tpool.n_workers;
	chunk = (app->phys.n + w - 1) / w;
	i = 0;
	while (i < w)
	{
		app->phys.integrate_jobs[i].app = app;
		app->phys.integrate_jobs[i].start = i * chunk;
		app->phys.integrate_jobs[i].end = i * chunk + chunk;
		if (app->phys.integrate_jobs[i].end > app->phys.n)
			app->phys.integrate_jobs[i].end = app->phys.n;
		app->phys.integrate_jobs[i].dt = dt;
		if (app->phys.integrate_jobs[i].start < app->phys.n)
			tpool_submit(&app->pool.tpool, integrate_chunk,
				&app->phys.integrate_jobs[i]);
		i++;
	}
	tpool_wait(&app->pool.tpool);
}

void	integrate(t_app *app, float dt)
{
	int	i;

	if (app->phys.n >= 64 && app->pool.tpool.n_workers > 1)
	{
		integrate_parallel(app, dt);
		return ;
	}
	i = 0;
	while (i < app->phys.n)
		integrate_body(app, &app->phys.bodies[i++], dt);
}
