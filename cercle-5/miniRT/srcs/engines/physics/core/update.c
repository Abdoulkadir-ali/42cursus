/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:04:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 22:45:00 by abdoali          ###   ########.fr       */
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

/**
 * @brief Main Entry Point for Physics Subsystem
 * 
 * Performance Note: Render BVH rebuild was removed from the physics step
 * as broadphase now relies on the specialized DBVT and Static BVH.
 */
void	update_physics(t_scene *scene, double dt)
{
	t_contact	contacts[MAX_CONTACTS];
	int			num_contacts;

	if (!scene)
		return ;
	integrate_and_ccd(scene, dt);
	num_contacts = generate_contacts(scene, contacts, MAX_CONTACTS);
	ft_print_debug("Physics: %d contacts, dt=%.4f\n", num_contacts, dt);
	solve_contact_iterations(contacts, num_contacts);
}
