/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 12:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "thread.h"

typedef struct s_int_task
{
	t_scene				*sc;
	double				dt;
	t_physics_settings	*s;
	size_t				next;
}	t_int_task;

static void	*sph_worker(void *p)
{
	t_int_task	*t = p;
	size_t		i;

	while (1)
	{
		i = __sync_fetch_and_add(&t->next, 1);
		if (i >= t->sc->sphere_count) break ;
		integrate_sphere(&t->sc->spheres[i], t->dt, t->s);
	}
	return (NULL);
}

static void	*box_worker(void *p)
{
	t_int_task	*t = p;
	size_t		i;

	while (1)
	{
		i = __sync_fetch_and_add(&t->next, 1);
		if (i >= t->sc->box_count) break ;
		integrate_box(&t->sc->boxes[i], t->dt, t->s);
	}
	return (NULL);
}

static void	*tri_worker(void *p)
{
	t_int_task	*t = p;
	size_t		i;

	while (1)
	{
		i = __sync_fetch_and_add(&t->next, 1);
		if (i >= t->sc->tri_count) break ;
		integrate_tri(&t->sc->tris[i], t->dt, t->s);
	}
	return (NULL);
}

static void	*cyl_worker(void *p)
{
	t_int_task	*t = p;
	size_t		i;

	while (1)
	{
		i = __sync_fetch_and_add(&t->next, 1);
		if (i >= t->sc->cylinder_count) break ;
		integrate_cylinder(&t->sc->cylinders[i], t->dt, t->s);
	}
	return (NULL);
}

/**
 * @brief Integrates all physical bodies in the scene using parallel workers.
 */
void	integrate_bodies_worker(t_scene *se, t_physic_engine *en, double dt)
{
	t_int_task	t;
	size_t i;

	if (!se || !en)
		return ;
	t = (t_int_task){se, dt, &en->settings, 0};
	parallel_run(se->pool, se->sphere_count, sph_worker, &t);
	t.next = 0;
	parallel_run(se->pool, se->box_count, box_worker, &t);
	t.next = 0;
	parallel_run(se->pool, se->tri_count, tri_worker, &t);
	t.next = 0;
	parallel_run(se->pool, se->cylinder_count, cyl_worker, &t);
	i = 0;
	while (i < se->pyramid_count)
		integrate_pyramid(&se->pyramids[i++], dt, t.s);
	i = 0;
	while (i < se->rect_count)
		integrate_rect(&se->rects[i++], dt, t.s);
}

/**
 * @brief Top-level physics update step.
 */
void	update_physics(t_scene *scene, t_physic_engine *engine, double dt)
{
	t_contact	contacts[MAX_CONTACTS];
	size_t		count;
	size_t		i;

	if (!scene || !engine || dt < 1e-6)
		return ;
	dt *= engine->settings.time_scale;
	integrate_bodies_worker(scene, engine, dt);
	i = 0;
	while (i < engine->settings.solver_iterations)
	{
		count = generate_contacts(scene, engine, contacts, MAX_CONTACTS);
		if (count > 0)
		{
			solve_velocities(contacts, engine, count);
			solve_positions(contacts, engine, count);
		}
		i++;
	}
}
