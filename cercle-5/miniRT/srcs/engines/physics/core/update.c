/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:04:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:04:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	integrate_and_ccd(t_scene *scene, double dt)
{
	int i;

	integrate_bodies(scene, dt);
	/* CDC Pass: Prevent tunneling for high-speed objects */
	i = -1;
	while (++i < scene->sphere_count)
		phys_resolve_ccd(scene, &scene->spheres[i].phys, dt);
	i = -1;
	while (++i < scene->box_count)
		phys_resolve_ccd(scene, &scene->boxes[i].phys, dt);
	phys_debug_spheres(scene);
}

static int	rebuild_bvh_and_generate_contacts(t_scene *scene,
		t_contact *contacts, int max_contacts)
{
	if (scene->bvh)
		bvh_destroy(scene->bvh);
	scene->bvh = bvh_create(scene);
	return (generate_contacts(scene, contacts, max_contacts));
}

static void	solve_contact_iterations(t_contact *contacts, int num_contacts)
{
	int i;

	if (num_contacts <= 0)
		return ;
	i = 0;
	while (i < SOLVER_ITERATIONS)
	{
		solve_velocities(contacts, num_contacts);
		solve_positions(contacts, num_contacts);
		i++;
	}
}

/*
 * Main Entry Point for Physics Subsystem
 * Pipeline:
 * 1. Integrate: Apply forces (gravity) and update velocities/positions.
 * 2. Collision Detection: Generate contact manifold via BVH broadphase.
 * 3. Solve: Iteratively resolve velocity and position constraints.
 * Note: BVH is rebuilt by the caller (update_physics_step in loop.c)
 *       after all substeps to avoid redundant rebuilds.
 */
void	update_physics(t_scene *scene, double dt)
{
	t_contact contacts[MAX_CONTACTS];
	int num_contacts;

	if (!scene)
		return ;
	integrate_and_ccd(scene, dt);
	num_contacts = rebuild_bvh_and_generate_contacts(scene, contacts,
			MAX_CONTACTS);
	ft_print_debug("Physics: %d contacts, dt=%.4f\n", num_contacts, dt);
	solve_contact_iterations(contacts, num_contacts);
}
