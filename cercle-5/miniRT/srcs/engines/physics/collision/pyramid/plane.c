/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:33:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

int	pyramid_vs_plane(t_pyramid *py, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3	v[5];
	t_vec3	ref;
	t_vec3	r;
	t_vec3	f;
	t_vec3	to_v;
	int		count;
	int		i;
	t_vec3	n;
	double	h;

	count = 0;
	i = -1;
	n = vec3_norm(pl->transform.up);
	h = py->base_size * 0.5;
	ref = (fabs(py->up.y) < 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
	r = vec3_norm(vec3_cross(py->up, ref));
	f = vec3_cross(r, py->up);
	v[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(r, h)), vec3_scale(f,
				h));
	v[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(r, -h)),
			vec3_scale(f, h));
	v[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(r, -h)),
			vec3_scale(f, -h));
	v[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(r, h)), vec3_scale(f,
				-h));
	v[4] = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
	while (++i < 5 && count < max_c)
	{
		to_v = vec3_sub(v[i], pl->transform.pos);
		if (vec3_dot(to_v, n) < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0);
			c[count].penetration = -vec3_dot(to_v, n);
			c[count].a = &py->phys;
			c[count].b = NULL;
			c[count].ta = &py->transform;
			c[count].tb = &pl->transform;
			c[count].contact_point = v[i];
			c[count].ra = vec3_sub(v[i], py->phys.center);
			c[count].rb = vec3(0, 0, 0);
			c[count].restitution = fmin(py->phys.elasticity, 0.5);
			c[count].friction = sqrt(py->phys.friction * 0.5);
			count++;
		}
	}
	return (count);
}
