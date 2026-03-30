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
	t_vec3	u_ax;
	t_vec3	v_ax;
	double	u_v[2];
	t_vec3	diff;

	vec3_orthonormal_basis(cy->transform.forward, &u_ax, &v_ax);
	if (cap)
	{
		diff = vec3_sub(pt.p, pt.center);
		hit->u = (vec3_dot(diff, u_ax) / pt.radius + 1) * 0.5;
		hit->v = (vec3_dot(diff, v_ax) / pt.radius + 1) * 0.5;
		hit->tangent = u_ax;
		hit->bitangent = v_ax;
	}
	else
	{
		u_v[0] = vec3_dot(vec3_sub(pt.p, pt.center), u_ax);
		u_v[1] = vec3_dot(vec3_sub(pt.p, pt.center), v_ax);
		hit->u = (atan2(u_v[1], u_v[0]) + M_PI) / (2 * M_PI);
		hit->v = pt.h / pt.height;
		hit->tangent = vec3_norm(vec3_cross(hit->normal,
					cy->transform.forward));
		hit->bitangent = vec3_norm(vec3_cross(hit->normal, hit->tangent));
	}
}
