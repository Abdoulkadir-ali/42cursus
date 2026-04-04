/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Calculates UV coordinates and tangent space for a cylinder.
*/
void	get_cylinder_uv(t_entry_point pt, t_cylinder *cy, t_hit *hit, bool cap)
{
	double	u_v[2];
	t_vec3	diff;

	if (cap)
	{
		diff = vec3_sub(pt.p, pt.center);
		hit->u = (vec3_dot(diff, cy->local_u) / pt.radius + 1) * 0.5;
		hit->v = (vec3_dot(diff, cy->local_v) / pt.radius + 1) * 0.5;
		hit->tangent = cy->local_u;
		hit->bitangent = cy->local_v;
	}
	else
	{
		u_v[0] = vec3_dot(vec3_sub(pt.p, pt.center), cy->local_u);
		u_v[1] = vec3_dot(vec3_sub(pt.p, pt.center), cy->local_v);
		hit->u = (atan2(u_v[1], u_v[0]) + M_PI) / (2 * M_PI);
		hit->v = pt.h / pt.height;
		hit->tangent = vec3_norm(vec3_cross(hit->normal,
					cy->transform.forward));
		hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
	}
}
