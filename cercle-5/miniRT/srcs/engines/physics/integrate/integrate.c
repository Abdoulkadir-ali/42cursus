/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 10:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Dispatcher for internal shape integrators.
 */
static void	loop_other_bodies(t_scene *scene, double dt, t_physics_settings *s)
{
	size_t	i;

	i = 0;
	while (i < scene->box_count)
		integrate_box(&scene->boxes[i++], dt, s);
	i = 0;
	while (i < scene->capsule_count)
		integrate_capsule(&scene->capsules[i++], dt, s);
	i = 0;
	while (i < scene->tri_count)
		integrate_tri(&scene->tris[i++], dt, s);
	i = 0;
	while (i < scene->cylinder_count)
		integrate_cylinder(&scene->cylinders[i++], dt, s);
}

/**
 * @brief Integrates all physical bodies in the scene.
 */
void	integrate_bodies(t_scene *scene, t_physic_engine *engine, double dt)
{
	t_physics_settings	*s;
	size_t				i;

	if (!scene || !engine)
		return ;
	s = &engine->settings;
	i = 0;
	while (i < scene->sphere_count)
		integrate_sphere(&scene->spheres[i++], dt, s);
	i = 0;
	while (i < scene->rect_count)
		integrate_rect(&scene->rects[i++], dt, s);
	i = 0;
	while (i < scene->pyramid_count)
		integrate_pyramid(&scene->pyramids[i++], dt, s);
	loop_other_bodies(scene, dt, s);
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
	integrate_bodies(scene, engine, dt);
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
