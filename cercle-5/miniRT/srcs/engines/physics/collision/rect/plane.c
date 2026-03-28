/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:05:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	rect_vs_plane(t_physics *phys, int idx, t_contact *c, int count, int max)
{
	t_rect	rc;
	t_plane	pl;
	t_vec3	to_v;
	int		i;
	t_vec3	v[4];
	t_vec3	right;
	t_vec3	up;

	rc = unpack_rect(&phys->scene->primitives, idx);
	right = vec3_norm(vec3_cross(rc.normal, vec3(0, 1, 0)));
	if (vec3_mag(right) < 0.001)
		right = vec3_norm(vec3_cross(rc.normal, vec3(1, 0, 0)));
	up = vec3_norm(vec3_cross(rc.normal, right));
	v[0] = vec3_add(rc.pos, vec3_add(vec3_scale(right, rc.ex), vec3_scale(up, rc.ey)));
	v[1] = vec3_add(rc.pos, vec3_sub(vec3_scale(right, rc.ex), vec3_scale(up, rc.ey)));
	v[2] = vec3_sub(rc.pos, vec3_add(vec3_scale(right, rc.ex), vec3_scale(up, rc.ey)));
	v[3] = vec3_sub(rc.pos, vec3_sub(vec3_scale(right, rc.ex), vec3_scale(up, rc.ey)));
	i = -1;
	while (++i < (int)phys->scene->primitives.count && count < max)
	{
		if (phys->scene->primitives.types[i] != PRIM_PLANE)
			continue ;
		pl = unpack_plane(&phys->scene->primitives, i);
		int p_idx = -1;
		while (++p_idx < 4 && count < max)
		{
			to_v = vec3_sub(v[p_idx], pl.point);
			if (vec3_dot(to_v, pl.normal) < 0.0)
			{
				c[count].normal = vec3_scale(pl.normal, -1.0);
				c[count].penetration = -vec3_dot(to_v, pl.normal);
				c[count].idx_a = idx;
				c[count].idx_b = i;
				c[count].contact_point = v[p_idx];
				c[count].ra = vec3_sub(v[p_idx], rc.pos);
				c[count].rb = vec3(0, 0, 0);
				c[count].restitution = phys->soa->elasticity[idx];
				c[count].friction = phys->soa->friction[idx];
				count++;
			}
		}
	}
	return (count);
}
