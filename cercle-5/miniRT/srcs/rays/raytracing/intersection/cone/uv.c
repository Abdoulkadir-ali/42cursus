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
** Calculates UV coordinates and tangent space for a cone intersection.
*/
void	get_cone_uv(t_hit *hit, t_cone *cone, t_vec3 radial, double h)
{
	t_vec3	u_ax;
	t_vec3	v_ax;
	double	dot;

	vec3_orthonormal_basis(cone->transform.forward, &u_ax, &v_ax);
	dot = vec3_dot(radial, u_ax);
	hit->u = (dot / cone->transform.scale.x + 1) * 0.5;
	hit->v = h / cone->transform.scale.y;
	hit->tangent = u_ax;
	hit->bitangent = v_ax;
}
