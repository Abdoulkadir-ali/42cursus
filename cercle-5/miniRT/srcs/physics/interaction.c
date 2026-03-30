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
		if (hit.ref.type == TYPE_SPHERE)
			phys = &scene->spheres[hit.ref.index].phys;
		else if (hit.ref.type == TYPE_TRI)
			phys = &scene->tris[hit.ref.index].phys;
		else if (hit.ref.type == TYPE_RECT)
			phys = &scene->rects[hit.ref.index].phys;
		else if (hit.ref.type == TYPE_PYRAMID)
			phys = &scene->pyramids[hit.ref.index].phys;
		else if (hit.ref.type == TYPE_BOX)
			phys = &scene->boxes[hit.ref.index].phys;
		else if (hit.ref.type == TYPE_CAPSULE)
			phys = &scene->capsules[hit.ref.index].phys;
		else if (hit.ref.type == TYPE_CYLINDER)
			phys = &scene->cylinders[hit.ref.index].phys;

		if (phys && !phys->is_static)
		{
			if (phys->mass > 1e-6)
			{
				t_vec3 delta_v = vec3_scale(ray.direction, impulse / phys->mass);
				phys->velocity = vec3_add(phys->velocity, delta_v);
				t_vec3 center_pos = phys->center;
				t_vec3 hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, hit.t));
				t_vec3 r = vec3_sub(hit_point, center_pos);
				t_vec3 force_vec = vec3_scale(ray.direction, impulse);
				t_vec3 torque = vec3_cross(r, force_vec);
				double inv_m = 1.0 / phys->mass;
				if (vec3_mag_sq(r) > 1e-6)
				{
					double inv_i = 2.5 * inv_m / fmax(vec3_mag_sq(r), 1.0);
					t_vec3 dw = vec3_scale(torque, inv_i);
					if (hit.ref.type == TYPE_CYLINDER)
					{
						t_vec3 ax = vec3_norm(
							scene->cylinders[hit.ref.index].transform.forward);
						dw = vec3_sub(dw,
							vec3_scale(ax, vec3_dot(dw, ax)));
					}
					phys->angular_velocity = vec3_add(
						phys->angular_velocity, dw);
				}
			}
		}
	}
}
