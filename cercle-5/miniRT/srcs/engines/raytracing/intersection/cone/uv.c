/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:55:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	get_cone_uv(t_hit *hit, t_primitive_array *p, int idx, t_vec3 radial,
		double h)
{
	t_vec3	u_ax;
	t_vec3	v_ax;
	t_vec3	axis;
	double	dot;

	axis = vec3(p->ax[idx], p->ay[idx], p->az[idx]);
	vec3_orthonormal_basis(axis, &u_ax, &v_ax);
	dot = vec3_dot(radial, u_ax);
	hit->u = (dot / p->radii[idx] + 1) * 0.5;
	hit->v = h / p->heights[idx];
}
