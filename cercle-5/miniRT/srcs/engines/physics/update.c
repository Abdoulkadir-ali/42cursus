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
    t_contact   *contacts;
    int         num_contacts;
    int         i;

    if (!scene)
        return ;
    contacts = malloc(sizeof(t_contact) * MAX_CONTACTS);
    if (!contacts)
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
    free(contacts);
}

/* Helper for refract_ray (moved from old physics.c) */
t_vec3	refract_ray(t_vec3 incident, t_vec3 normal, float n1, float n2)
{
	float	cosi;
	float	eta;
	float	k;
	t_vec3	part1;
	t_vec3	part2;

	cosi = fmaxf(-1.0f, fminf(1.0f, (float)vec3_dot(incident, normal)));
	eta = n1 / n2;
	k = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (k < 0.0f)
		return ((t_vec3){0, 0, 0, 0});
	part1 = vec3_scale(incident, eta);
	part2 = vec3_scale(normal, eta * cosi - sqrtf(k));
	return (vec3_add(part1, part2));
}
