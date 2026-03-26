/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"
#include "scene.h"
#include "debug.h"

/* 
 * Main Entry Point for Physics Subsystem
 * Pipeline:
 * 1. Integrate: Apply forces (gravity) and update velocities/positions.
 * 2. Collision Detection: Generate contact manifold via BVH broadphase.
 * 3. Solve: Iteratively resolve velocity and position constraints.
 * Note: BVH is rebuilt by the caller (update_physics_step in loop.c)
 *       after all substeps to avoid redundant rebuilds.
 */
void update_physics(t_scene *scene, double dt)
{
    t_contact   contacts[MAX_CONTACTS];
    int         num_contacts;
    int         i;

    if (!scene)
        return ;
    integrate_bodies(scene, dt);
    phys_debug_spheres(scene);
    if (scene->bvh)
        bvh_destroy(scene->bvh);
    scene->bvh = bvh_create(scene);
    num_contacts = generate_contacts(scene, contacts, MAX_CONTACTS);
    ft_print_debug("Physics: %d contacts, dt=%.4f\n", num_contacts, dt);
    if (num_contacts > 0)
    {
        i = 0;
        while (i < SOLVER_ITERATIONS)
        {
            solve_velocities(contacts, num_contacts);
            solve_positions(contacts, num_contacts);
            i++;
        }
    }
}

