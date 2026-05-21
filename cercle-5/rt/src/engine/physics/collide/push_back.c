/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:41:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

static void	push_one(t_body *b, t_object *o, int *moved)
{
	float	heat_glow;
	t_vec3	old;
	t_vec3	dd;

	if (b->inv_mass > 0.0f)
	{
		old = object_center(o);
		object_translate_to(o, b->pos);
		dd = v3_sub(b->pos, old);
		if (v3_dot(dd, dd) > 1e-10f)
			*moved = 1;
	}
	o->mat.temperature = b->temperature;
	if (b->temperature > 800.0f)
	{
		heat_glow = (b->temperature - 800.0f) / 1500.0f;
		if (heat_glow > 4.0f)
			heat_glow = 4.0f;
		if (heat_glow > o->mat.emission)
			o->mat.emission = heat_glow;
	}
}

static void	pushback_chunk(void *data)
{
	t_pushback_job	*j;
	t_body			*b;
	int				i;

	j = (t_pushback_job *)data;
	i = j->start;
	while (i < j->end)
	{
		b = &j->app->phys.bodies[i];
		if (b->sphere_idx >= 0 && (size_t)b->sphere_idx < j->app->scene.n_bvh)
			push_one(b, &j->app->scene.bvh_objs[b->sphere_idx], &j->moved);
		i++;
	}
}

static int	pushback_parallel(t_app *app)
{
	int	n;
	int	w;
	int	chunk;
	int	i;
	int	moved;

	n = app->phys.n;
	w = app->pool.tpool.n_workers;
	chunk = (n + w - 1) / w;
	i = 0;
	while (i < w)
	{
		app->phys.pushback_jobs[i] = (t_pushback_job){app, i * chunk,
			i * chunk + chunk, 0};
		if (app->phys.pushback_jobs[i].end > n)
			app->phys.pushback_jobs[i].end = n;
		if (app->phys.pushback_jobs[i].start < n)
			tpool_submit(&app->pool.tpool, pushback_chunk,
				&app->phys.pushback_jobs[i]);
		i++;
	}
	tpool_wait(&app->pool.tpool);
	moved = 0;
	i = 0;
	while (i < w)
		moved |= app->phys.pushback_jobs[i++].moved;
	return (moved);
}

int	push_back_to_scene(t_app *app)
{
	t_body		*b;
	int			moved;
	int			i;

	if (app->phys.n >= 64 && app->pool.tpool.n_workers > 1)
		return (pushback_parallel(app));
	moved = 0;
	i = 0;
	while (i < app->phys.n)
	{
		b = &app->phys.bodies[i];
		if (b->sphere_idx >= 0 && (size_t)b->sphere_idx < app->scene.n_bvh)
			push_one(b, &app->scene.bvh_objs[b->sphere_idx], &moved);
		i++;
	}
	return (moved);
}
