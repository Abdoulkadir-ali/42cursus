/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 19:29:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "thread.h"
#include "raytracing.h"

static void	*universal_worker(void *p)
{
	t_int_task	*t;
	size_t		i;

	t = p;
	while (1)
	{
		i = __sync_fetch_and_add(&t->next, 1);
		if (t->type == INT_SPH && i < t->sc->sphere_count)
			integrate_sphere(&t->sc->spheres[i], t->dt, t->s);
		else if (t->type == INT_BOX && i < t->sc->box_count)
			integrate_box(&t->sc->boxes[i], t->dt, t->s);
		else if (t->type == INT_TRI && i < t->sc->tri_count)
			integrate_tri(&t->sc->tris[i], t->dt, t->s);
		else if (t->type == INT_CYL && i < t->sc->cylinder_count)
			integrate_cylinder(&t->sc->cylinders[i], t->dt, t->s);
		else if (t->type == INT_PYR && i < t->sc->pyramid_count)
			integrate_pyramid(&t->sc->pyramids[i], t->dt, t->s);
		else if (t->type == INT_RECT && i < t->sc->rect_count)
			integrate_rect(&t->sc->rects[i], t->dt, t->s);
		else if (t->type == INT_CAP && i < t->sc->capsule_count)
			integrate_capsule(&t->sc->capsules[i], t->dt, t->s);
		else
			break ;
	}
	return (NULL);
}

/**
 * @brief Integrates all physical bodies in the scene using parallel workers.
 */
static void	run_int_passes(t_scene *se, t_int_task *t)
{
	t->next = 0;
	t->type = INT_CYL;
	parallel_run(se->pool, se->cylinder_count, universal_worker, t);
	t->next = 0;
	t->type = INT_PYR;
	parallel_run(se->pool, se->pyramid_count, universal_worker, t);
	t->next = 0;
	t->type = INT_RECT;
	parallel_run(se->pool, se->rect_count, universal_worker, t);
	t->next = 0;
	t->type = INT_CAP;
	parallel_run(se->pool, se->capsule_count, universal_worker, t);
}

static void	bvh_sync(t_scene *scene)
{
	t_bvh	*new_bvh;
	t_bvh	*old;

	new_bvh = bvh_create(scene);
	if (!new_bvh)
		return ;
	pthread_rwlock_wrlock(&scene->bvh_lock);
	old = scene->bvh;
	scene->bvh = new_bvh;
	pthread_rwlock_unlock(&scene->bvh_lock);
	bvh_destroy(old);
}

void	integrate_bodies_worker(t_scene *se, t_physic_engine *en, double dt)
{
	t_int_task	t;

	if (!se || !en)
		return ;
	t = (t_int_task){se, dt, &en->settings, 0, INT_SPH};
	parallel_run(se->pool, se->sphere_count, universal_worker, &t);
	t.next = 0;
	t.type = INT_BOX;
	parallel_run(se->pool, se->box_count, universal_worker, &t);
	t.next = 0;
	t.type = INT_TRI;
	parallel_run(se->pool, se->tri_count, universal_worker, &t);
	run_int_passes(se, &t);
}

void	update_physics(t_scene *scene, t_physic_engine *engine, double dt)
{
	static t_contact	contacts[MAX_CONTACTS];
	size_t				count;
	size_t				i;

	if (!scene || !engine || dt < 1e-6)
		return ;
	dt *= engine->settings.time_scale;
	sync_phys_settings(scene, engine);
	apply_attractor_pass(scene, &engine->settings);
	integrate_bodies_worker(scene, engine, dt);
	bvh_sync(scene);
	count = generate_contacts(scene, engine, contacts, MAX_CONTACTS);
	if (count == 0)
		return ;
	i = 0;
	while (i < engine->settings.solver_iterations)
	{
		solve_velocities(contacts, engine, count);
		solve_positions(contacts, engine, count);
		i++;
	}
}
