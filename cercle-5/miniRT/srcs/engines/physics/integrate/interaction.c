/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 10:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"
/**
 * @brief Retrieves the physics body associated with a ray hit reference.
 */
static t_physics_body	*get_hit_phys(t_scene *s, t_bvh_ref ref)
{
	if (ref.type == TYPE_SPHERE)
		return (&s->spheres[ref.index].phys);
	if (ref.type == TYPE_TRI)
		return (&s->tris[ref.index].phys);
	if (ref.type == TYPE_RECT)
		return (&s->rects[ref.index].phys);
	if (ref.type == TYPE_PYRAMID)
		return (&s->pyramids[ref.index].phys);
	if (ref.type == TYPE_BOX)
		return (&s->boxes[ref.index].phys);
	if (ref.type == TYPE_CAPSULE)
		return (&s->capsules[ref.index].phys);
	if (ref.type == TYPE_CYLINDER)
		return (&s->cylinders[ref.index].phys);
	return (NULL);
}

/**
 * @brief Applies rotational impulse based on hit point and torque.
 */
static void	apply_torque(t_physics_body *ph, t_vec3 hit, double imp,
		t_bvh_ref r)
{
	t_vec3	ra;
	t_vec3	dw;
	t_vec3	ax;

	ra = vec3_sub(hit, ph->center);
	if (vec3_mag_sq(ra) < 1e-6)
		return ;
	dw = vec3_scale(vec3_cross(ra, vec3_scale(ra, imp)),
			2.5 / (ph->mass * vec3_mag_sq(ra)));
	if (r.type == TYPE_CYLINDER)
	{
		ax = vec3_norm(ph->pos);
		dw = vec3_sub(dw, vec3_scale(ax, vec3_dot(dw, ax)));
	}
	ph->angular_velocity = vec3_add(ph->angular_velocity, dw);
}

/**
 * @brief Casts a ray and applies a physical impulse to the first dynamic hit.
 */
void	physics_shoot_ray(t_scene *s, t_ray ray, double impulse)
{
	t_hit			h;
	t_physics_body	*ph;
	t_vec3			hit_p;

	if (!s || !s->bvh)
		return ;
	h.t = 1e30;
	if (!bvh_intersect(s->bvh, &ray, &h))
		return ;
	ph = get_hit_phys(s, h.ref);
	if (!ph || ph->is_static || ph->mass < 1e-6)
		return ;
	ph->velocity = vec3_add(ph->velocity,
			vec3_scale(ray.direction, impulse / ph->mass));
	hit_p = vec3_add(ray.origin, vec3_scale(ray.direction, h.t));
	apply_torque(ph, hit_p, impulse, h.ref);
}
