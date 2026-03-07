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
    
    /* 1. Integrate Forces & Velocity */
    integrate_bodies(scene, dt);
    phys_debug_spheres(scene);

    /* 2. Collision Detection (Broad + Narrow) */
    if (scene->bvh)
        bvh_destroy(scene->bvh);
    scene->bvh = bvh_create(scene);
    num_contacts = generate_contacts(scene, contacts, MAX_CONTACTS);

    /* Debug: print collision info */
    ft_print_debug("Physics: %d contacts, dt=%.4f\n", num_contacts, dt);
    i = 0;
    while (i < num_contacts)
    {
        ft_print_debug("  C[%d] pen=%.4f n=(%.2f,%.2f,%.2f) "
            "ra=(%.2f,%.2f,%.2f)\n", i, contacts[i].penetration,
            contacts[i].normal.x, contacts[i].normal.y,
            contacts[i].normal.z, contacts[i].ra.x,
            contacts[i].ra.y, contacts[i].ra.z);
        i++;
    }

    /* 3. Solve Constraints */
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

/* Stubs for API compatibility if called elsewhere */
void resolve_collisions(t_scene *scene, struct s_sphere *sp)
{
    (void)scene;
    (void)sp;
}

void apply_gravity(t_scene *scene, float delta_time)
{
    (void)scene;
    (void)delta_time;
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

bool detect_sphere_sphere_collision(const t_sphere *a, const t_sphere *b,
	t_vec3 *out_normal, double *out_penetration)
{
    t_contact c;
    /* const cast for compatibility with new solver signature */
    if (collide_sphere_sphere((t_sphere *)a, (t_sphere *)b, &c))
    {
        if (out_normal) *out_normal = c.normal;
        if (out_penetration) *out_penetration = c.penetration;
        return (true);
    }
    return (false);
}

/* Exposed for API compatibility */
bool detect_sphere_plane_collision(const t_sphere *s, const t_plane *pl,
    t_vec3 *out_normal, double *out_penetration)
{
    t_contact c;
    if (collide_sphere_plane((t_sphere*)s, (t_plane*)pl, &c))
    {
        if (out_normal) *out_normal = c.normal;
        if (out_penetration) *out_penetration = c.penetration;
        return (true);
    }
    return (false);
}

/* Helper for generic collider API */
bool detect_collider_collision(const t_collider *A, const t_transform *Ta,
    const t_collider *B, const t_transform *Tb, t_vec3 *out_normal, double *out_penetration)
{
    /* Minimal implementation for fallback/helpers */
    if (A->type == COLLIDER_SPHERE && B->type == COLLIDER_SPHERE)
    {
        t_sphere sa, sb;
        sa.transform = *Ta; sa.radius_sq = A->data.radius * A->data.radius;
        sa.phys.elasticity = 0.5; sa.phys.mass = 1.0;
        sb.transform = *Tb; sb.radius_sq = B->data.radius * B->data.radius;
        sb.phys.elasticity = 0.5; sb.phys.mass = 1.0;
        return detect_sphere_sphere_collision(&sa, &sb, out_normal, out_penetration);
    }
    return (false);
}
