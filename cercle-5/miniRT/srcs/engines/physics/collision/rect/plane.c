/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	rect_vs_plane(t_rect *rc, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3	n;
	t_vec3	to_v;
	double	dist;
	int		count;
	int		i;

	n = vec3_norm(pl->transform.up);
	count = 0;
	i = 0;
	while (i < 4 && count < max_c)
	{
		to_v = vec3_sub(rc->v[i], pl->transform.pos);
		dist = vec3_dot(to_v, n);
		if (dist < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0);
			c[count].penetration = -dist;
			c[count].a = &rc->phys;
			c[count].b = NULL;
			c[count].ta = &rc->transform;
			c[count].tb = &pl->transform;
			c[count].contact_point = rc->v[i];
			c[count].ra = vec3_sub(rc->v[i], rc->phys.center);
			c[count].rb = vec3(0, 0, 0);
			c[count].restitution = fmin(rc->phys.elasticity, 0.5);
			c[count].friction = sqrt(rc->phys.friction * 0.5);
			count++;
		}
		i++;
	}
	return (count);
}
