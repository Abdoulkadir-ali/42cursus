/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 15:08:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "particles.h"
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

static void	rebuild_sb_mesh_bvhs(t_scene *scene)
{
	size_t		i;
	t_soft_body	*sb;

	i = 0;
	while (i < scene->soft_body_count)
	{
		sb = &scene->soft_bodies[i];
		if (sb->active && sb->mesh_idx < scene->mesh_count)
			mesh_build_bvh(&scene->meshes[sb->mesh_idx]);
		i++;
	}
}

static void	bvh_sync(t_scene *scene)
{
	t_bvh	*new_bvh;
	t_bvh	*old;

	pthread_rwlock_wrlock(&scene->bvh_lock);
	rebuild_sb_mesh_bvhs(scene);
	pthread_rwlock_unlock(&scene->bvh_lock);
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

static uint32_t	hash_contact(t_physics_body *a, t_physics_body *b)
{
	uintptr_t	p1;
	uintptr_t	p2;

	p1 = (uintptr_t)a;
	p2 = (uintptr_t)b;
	if (p1 > p2)
	{
		p1 = (uintptr_t)b;
		p2 = (uintptr_t)a;
	}
	return ((uint32_t)(p1 ^ (p2 >> 4)));
}

static void	warm_start(t_physic_engine *en)
{
	size_t		i;
	t_contact	*ct;
	double		ia;
	double		ib;

	i = 0;
	while (i < en->contact_count)
	{
		ct = &en->contacts[i];
		ia = get_inv_mass(ct->a);
		ib = get_inv_mass(ct->b);
		/* Ghost rule: do not warm-start contacts involving zero-mass
		   non-static bodies — they carry no meaningful accumulated impulse. */
		if ((ia < 1e-15 && ct->a && !ct->a->is_static)
			|| (ib < 1e-15 && ct->b && !ct->b->is_static))
		{
			i++;
			continue ;
		}
		if (fabs(ct->accum_n) > 1e-6)
		{
			wake_body(ct->a);
			wake_body(ct->b);
		}
		update_vel(ct, ia, ib, ct->accum_n);
		i++;
	}
}

static void	persist_contacts(t_physic_engine *en, t_contact *new_c, size_t count)
{
	size_t		i;
	size_t		j;
	uint32_t	h;

	i = 0;
	while (i < count)
	{
		h = hash_contact(new_c[i].a, new_c[i].b);
		new_c[i].hash = h;
		j = 0;
		while (j < en->contact_count)
		{
			if (en->contacts[j].hash == h)
			{
				new_c[i].accum_n = en->contacts[j].accum_n * 0.9;
				new_c[i].accum_t = en->contacts[j].accum_t * 0.9;
				break ;
			}
			j++;
		}
		i++;
	}
	en->contact_count = count;
	ft_memcpy(en->contacts, new_c, sizeof(t_contact) * count);
}

/**
 * @brief Propagates the "awake" state through the contact graph.
 *        A single sweep is repeated until no new body is woken, ensuring
 *        that a sleeping stack wakes atomically when its base is struck.
 *        Bounded by solver_iterations to avoid O(n²) cost in degenerate scenes.
 */
static void	wake_island(t_physic_engine *en)
{
	size_t		pass;
	size_t		i;
	bool		any;
	t_contact	*ct;

	pass = 0;
	while (pass++ < en->settings.solver_iterations)
	{
		any = false;
		i = 0;
		while (i < en->contact_count)
		{
			ct = &en->contacts[i++];
			if (ct->a && !ct->a->is_sleeping && ct->b && ct->b->is_sleeping
				&& !ct->b->is_static)
			{
				wake_body(ct->b);
				any = true;
			}
			if (ct->b && !ct->b->is_sleeping && ct->a && ct->a->is_sleeping
				&& !ct->a->is_static)
			{
				wake_body(ct->a);
				any = true;
			}
		}
		if (!any)
			break ;
	}
}

void	update_physics(t_scene *scene, t_physic_engine *engine, double dt)
{
	static t_contact	new_contacts[MAX_CONTACTS];
	size_t				count;
	size_t				i;

	if (!scene || !engine || dt < 1e-6)
		return ;
	dt *= engine->settings.time_scale;
	sync_phys_settings(scene, engine);
	apply_attractor_pass(scene, &engine->settings);
	apply_nbody_gravity(scene, engine->settings.big_g);
	apply_wind_pass(scene, &engine->settings, dt);
	integrate_bodies_worker(scene, engine, dt);
	soft_body_step(scene, dt, &engine->settings);
	particle_systems_step(scene, dt, &engine->settings);
	sync_thermal_to_materials(scene);
	bvh_sync(scene);
	count = generate_contacts(scene, engine, new_contacts, MAX_CONTACTS);
	persist_contacts(engine, new_contacts, count);
	if (engine->contact_count == 0)
		return ;
	warm_start(engine);
	wake_island(engine);
	i = 0;
	while (i < engine->settings.solver_iterations)
	{
		solve_velocities(engine->contacts, engine, engine->contact_count);
		solve_positions(engine->contacts, engine, engine->contact_count);
		i++;
	}
	/*
	** Re-clamp speeds after solver: impulse responses can push bodies above
	** MAX_SPEED, causing tunnelling on the next frame. Clamp here so the
	** position update at the start of the next step is always bounded.
	*/
	i = 0;
	while (i < scene->sphere_count)
		clamp_speed(&scene->spheres[i++].phys);
	i = 0;
	while (i < scene->box_count)
		clamp_speed(&scene->boxes[i++].phys);
	i = 0;
	while (i < scene->capsule_count)
		clamp_speed(&scene->capsules[i++].phys);
	i = 0;
	while (i < scene->cylinder_count)
		clamp_speed(&scene->cylinders[i++].phys);
	i = 0;
	while (i < scene->pyramid_count)
		clamp_speed(&scene->pyramids[i++].phys);
	i = 0;
	while (i < scene->rect_count)
		clamp_speed(&scene->rects[i++].phys);
}
