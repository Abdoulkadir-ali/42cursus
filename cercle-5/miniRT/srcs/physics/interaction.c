/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/16 20:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics_internal.h"
#include "raytracing.h"

/*
 * Casts a ray into the scene and applies an impulse to the first dynamic object hit.
 */
void	physics_shoot_ray(t_scene *scene, t_ray ray, double impulse)
{
	t_hit			hit;
	t_physics_body	*phys;

	if (!scene || !scene->bvh)
		return ;

	hit.t = 1e30;
	phys = NULL;

	if (bvh_intersect(scene->bvh, &ray, &hit))
	{
		/* Identify the object and get its physics body */
		if (hit.ref.type == TYPE_SPHERE)
			phys = &scene->spheres[hit.ref.index].phys;
		/* Add other types as needed */

		if (phys && !phys->is_static)
		{
			/* Apply Impulse: v += J / m * direction */
			/* Ensure mass is valid to avoid div by zero, though integrate fixes it */
			if (phys->mass > 1e-6)
			{
				/* Linear Impulse */
				t_vec3 delta_v = vec3_scale(ray.direction, impulse / phys->mass);
				phys->velocity = vec3_add(phys->velocity, delta_v);
				
				/* Angular Impulse (Torque) */
				/* Need transform position to calculate lever arm */
				t_vec3 center_pos;
				if (hit.ref.type == TYPE_SPHERE)
					center_pos = scene->spheres[hit.ref.index].transform.pos;
				else if (hit.ref.type == TYPE_MESH)
					center_pos = scene->meshes[hit.ref.index].transform.pos;
				else
					center_pos = (t_vec3){0}; /* Fallback or extend for other types */
					
				t_vec3 hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, hit.t));
				t_vec3 r = vec3_sub(hit_point, center_pos);
				t_vec3 force_vec = vec3_scale(ray.direction, impulse);
				t_vec3 torque = vec3_cross(r, force_vec);
				
				/* Estimate Inertia (Solid Sphere approx for all dynamic bodies for now) */
				/* I = 0.4 * mass * radius^2 */
				/* inv_I = 2.5 / (mass * radius^2) */
				/* We can use |r|^2 as approx radius^2 if hit is on surface */
				double r2 = vec3_mag_sq(r);
				if (r2 > 1e-6)
				{
					double inv_inertia = 2.5 / (phys->mass * r2);
					phys->angular_velocity = vec3_add(phys->angular_velocity, 
							vec3_scale(torque, inv_inertia));
				}

				printf("Physics: Impulse %.1f on Obj %d (Torque: %.2f)\n",
						impulse, hit.ref.index, vec3_mag(torque));
			}
		}
	}
}
