/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "objects.h"

int	tri_vs_plane(t_tri_shape *tr, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3 n = vec3_norm(pl->transform.up);
	t_vec3 to_v; double dist; int count = 0; int i = -1;

	while (++i < 3 && count < max_c)
	{
		to_v = vec3_sub(tr->v[i], pl->transform.pos);
		dist = vec3_dot(to_v, n);
		if (dist < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0); c[count].penetration = -dist;
			c[count].a = &tr->phys; c[count].b = NULL; c[count].ta = &tr->transform; c[count].tb = &pl->transform;
			c[count].contact_point = tr->v[i]; c[count].ra = vec3_sub(tr->v[i], tr->phys.center); c[count].rb = vec3(0,0,0);
			c[count].restitution = fmin(tr->phys.elasticity, 0.5); c[count].friction = sqrt(tr->phys.friction * 0.5);
			count++;
		}
	}
	return (count);
}
