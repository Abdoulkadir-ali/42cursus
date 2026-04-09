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
 * @brief Casts a ray and applies a physical impulse to the first dynamic hit.
 * Uses a scalar isotropic inertia estimate so the angular response stays
 * reasonable for any shape orientation.  For cylinders the spin-axis
 * component is stripped so they tip over instead of behaving like a beyblade.
 */
void	physics_shoot_ray(t_scene *s, t_ray ray, double impulse)
{
	t_hit		h;
	t_physics_body	*ph;
	t_vec3		hit_p;
	t_vec3		ra;
	t_vec3		torque;
	t_vec3		dw;
	double		inv_m;
	double		inv_i;
	t_vec3		ax;

	if (!s || !s->bvh)
		return ;
	h.t = 1e30;
	if (!bvh_intersect(s->bvh, &ray, &h))
		return ;
	ph = get_hit_phys(s, h.ref);
	if (!ph || ph->is_static || ph->mass < 1e-6)
		return ;
	inv_m = 1.0 / ph->mass;
	ph->velocity = vec3_add(ph->velocity,
			vec3_scale(ray.direction, impulse * inv_m));
	hit_p = vec3_add(ray.origin, vec3_scale(ray.direction, h.t));
	ra = vec3_sub(hit_p, ph->center);
	if (vec3_mag_sq(ra) < 1e-6)
		return ;
	torque = vec3_cross(ra, vec3_scale(ray.direction, impulse));
	inv_i = 2.5 * inv_m / fmax(vec3_mag_sq(ra), 1.0);
	dw = vec3_scale(torque, inv_i);
	if (h.ref.type == TYPE_CYLINDER)
	{
		ax = vec3_norm(s->cylinders[h.ref.index].transform.forward);
		dw = vec3_sub(dw, vec3_scale(ax, vec3_dot(dw, ax)));
	}
	ph->angular_velocity = vec3_add(ph->angular_velocity, dw);
}
