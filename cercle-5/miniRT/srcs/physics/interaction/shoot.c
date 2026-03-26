/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:36:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"
#include "scene.h"

void	physics_shoot_ray(t_scene *scene, t_ray ray, double impulse)
{
	t_hit			hit;
	t_physics_body	*phys;
	t_vec3			rad;
	t_vec3			dw;

	if (!scene || !scene->bvh || !bvh_intersect(scene->bvh, &ray, &hit))
		return ;
	phys = get_body_ref(scene, hit.ref);
	if (!phys || phys->is_static || phys->mass < 1e-6)
		return ;
	phys->velocity = vec3_add(phys->velocity,
			vec3_scale(ray.direction, impulse / phys->mass));
	rad = vec3_sub(vec3_add(ray.origin, vec3_scale(ray.direction, hit.t)),
			phys->center);
	if (vec3_mag_sq(rad) < 1e-6)
		return ;
	dw = vec3_scale(vec3_cross(rad, vec3_scale(ray.direction, impulse)),
			2.5 / (phys->mass * fmax(vec3_mag_sq(rad), 1.0)));
	if (hit.ref.type == TYPE_CYLINDER)
		dw = vec3_sub(dw, vec3_scale(vec3_norm(scene->cylinders[hit.ref.index]
					.transform.forward), vec3_dot(dw, vec3_norm(scene->cylinders[
						hit.ref.index].transform.forward))));
	phys->angular_velocity = vec3_add(phys->angular_velocity, dw);
}

