/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:48:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

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

static void	apply_physics_impulse(t_scene *s, t_physics_body *ph, t_hit *h,
				t_vec3 dir)
{
	t_vec3	ra;
	t_vec3	dw;
	double	inv_i;
	t_vec3	ax;

	ph->velocity = vec3_add(ph->velocity, vec3_scale(dir, 1.0 / ph->mass));
	ra = vec3_sub(h->point, ph->center);
	if (vec3_mag_sq(ra) < 1e-6)
		return ;
	inv_i = 2.5 / (ph->mass * fmax(vec3_mag_sq(ra), 1.0));
	dw = vec3_scale(vec3_cross(ra, dir), inv_i);
	if (h->ref.type == TYPE_CYLINDER)
	{
		ax = vec3_norm(s->cylinders[h->ref.index].transform.forward);
		dw = vec3_sub(dw, vec3_scale(ax, vec3_dot(dw, ax)));
	}
	ph->angular_velocity = vec3_add(ph->angular_velocity, dw);
}

void	physics_shoot_ray(t_scene *s, t_ray ray, double impulse)
{
	t_hit			h;
	t_physics_body	*ph;

	if (!s || !s->bvh)
		return ;
	h.t = 1e30;
	if (!bvh_intersect(s->bvh, &ray, &h))
		return ;
	ph = get_hit_phys(s, h.ref);
	if (!ph || ph->is_static || ph->mass < 1e-6)
		return ;
	apply_physics_impulse(s, ph, &h, vec3_scale(ray.direction, impulse));
}
