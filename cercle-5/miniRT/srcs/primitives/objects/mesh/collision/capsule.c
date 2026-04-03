/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:27:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

bool	detect_sphere_capsule_collision(const t_sphere *s,
	const t_collider *c, t_collision *out)
{
	t_vec3	ab;
	t_vec3	ap;
	t_vec3	pos;
	double	t;
	double	dist;

	ab = vec3_sub(c->data.capsule.b, c->data.capsule.a);
	ap = vec3_sub(s->transform.pos, c->data.capsule.a);
	t = vec3_dot(ap, ab) / vec3_dot(ab, ab);
	if (t < 0.0)
		t = 0.0;
	if (t > 1.0)
		t = 1.0;
	pos = vec3_add(c->data.capsule.a, vec3_scale(ab, t));
	dist = vec3_mag(vec3_sub(s->transform.pos, pos));
	if (dist > sqrt(s->radius_sq) + c->data.capsule.radius)
		return (false);
	out->best_normal = vec3_norm(vec3_sub(s->transform.pos, pos));
	out->best_pen = (sqrt(s->radius_sq) + c->data.capsule.radius) - dist;
	out->hit = true;
	return (true);
}
