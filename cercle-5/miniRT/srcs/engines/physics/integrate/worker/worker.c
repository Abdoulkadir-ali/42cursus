/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 13:10:00 by abdoali          ###   ########.fr       */
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
				any = (wake_body(ct->b), true);
			if (ct->b && !ct->b->is_sleeping && ct->a && ct->a->is_sleeping
				&& !ct->a->is_static)
				any = (wake_body(ct->a), true);
		}
		if (!any)
			break ;
	}
}

void	update_physics(t_scene *sc, t_physic_engine *en, double dt)
{
	static t_contact	new_c[MAX_CONTACTS];
	size_t				count;

	if (!sc || !en || dt < 1e-6)
		return ;
	dt *= en->settings.time_scale;
	sync_phys_settings(sc, en);
	apply_attractor_pass(sc, &en->settings);
	apply_nbody_gravity(sc, en->settings.big_g);
	apply_wind_pass(sc, &en->settings, dt);
	integrate_bodies_worker(sc, en, dt);
	soft_body_step(sc, dt, &en->settings);
	particle_systems_step(sc, dt, &en->settings);
	sync_thermal_to_materials(sc);
	bvh_sync(sc);
	count = generate_contacts(sc, en, new_c, MAX_CONTACTS);
	persist_contacts(en, new_c, count);
	if (en->contact_count == 0)
		return ;
	warm_start(en);
	wake_island(en);
	solve_all(en);
	clamp_all_speeds(sc);
}
