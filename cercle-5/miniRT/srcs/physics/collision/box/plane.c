/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 13:34:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

int	box_vs_plane(t_box *bx, t_plane *pl, t_contact *c, int max_c)
{
	t_vec3	ax[3];
	t_vec3	he;
	t_vec3	cor;
	t_vec3	to_c;
	int		count;
	int		i;
	t_vec3	n;

	count = 0;
	i = -1;
	n = vec3_norm(pl->transform.up);
	ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	he = bx->half_extents;
	while (++i < 8 && count < max_c)
	{
		cor = vec3_add(bx->phys.center, vec3_add(vec3_add(vec3_scale(ax[0],
							((i & 1) ? 1 : -1) * he.x), vec3_scale(ax[1],
							((i & 2) ? 1 : -1) * he.y)), vec3_scale(ax[2],
						((i & 4) ? 1 : -1) * he.z)));
		to_c = vec3_sub(cor, pl->transform.pos);
		if (vec3_dot(to_c, n) < 0.0)
		{
			c[count].normal = vec3_scale(n, -1.0);
			c[count].penetration = -vec3_dot(to_c, n);
			c[count].a = &bx->phys;
			c[count].b = NULL;
			c[count].ta = &bx->transform;
			c[count].tb = &pl->transform;
			c[count].contact_point = cor;
			c[count].ra = vec3_sub(cor, bx->phys.center);
			c[count].rb = vec3(0, 0, 0);
			c[count].restitution = fmin(bx->phys.elasticity, 0.5);
			c[count].friction = sqrt(bx->phys.friction * 0.5);
			count++;
		}
	}
	return (count);
}
