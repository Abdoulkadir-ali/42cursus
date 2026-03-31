/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "physics.h"
#include "mesh.h"

/**
 * Checks if a sphere collides with a capsule collider.
 * This is used as a simplified collision path for complex meshes.
 */
bool	detect_sphere_capsule_collision(const struct s_sphere *s,
			const t_collider *c, t_vec3 *out_normal, double *out_penetration)
{
	t_vec3	ab;
	t_vec3	as;
	t_vec3	closest;
	t_vec4	v;
	double	r_sum;

	ab = vec3_sub(c->data.capsule.b, c->data.capsule.a);
	as = vec3_sub(s->transform.pos, c->data.capsule.a);
	v.x = clamp_d(vec3_dot(as, ab) / vec3_dot(ab, ab), 0.0, 1.0);
	closest = vec3_add(c->data.capsule.a, vec3_scale(ab, v.x));
	v.y = vec3_mag_sq(vec3_sub(s->transform.pos, closest));
	r_sum = sqrt(s->radius_sq) + c->data.capsule.radius;
	if (v.y < r_sum * r_sum)
	{
		v.z = sqrt(v.y);
		if (out_normal)
			*out_normal = vec3_scale(vec3_sub(s->transform.pos, closest),
					1.0 / (v.z + 1e-6));
		if (out_penetration)
			*out_penetration = r_sum - v.z;
		return (true);
	}
	return (false);
}
