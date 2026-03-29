/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:46:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z, 0.0});
}

t_vec3	vec3_scale(t_vec3 a, double s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s, 0.0});
}

t_vec3	vec3_lerp(t_vec3 a, t_vec3 b, double t)
{
	return (vec3_add(a, vec3_scale(vec3_sub(b, a), t)));
}

t_vec3	vec3_norm(t_vec3 a)
{
	double	mag_sq;
	double	inv_mag;

	mag_sq = a.x * a.x + a.y * a.y + a.z * a.z;
	if (mag_sq < 1e-24)
		return ((t_vec3){0, 0, 0, 0});
	inv_mag = 1.0 / sqrt(mag_sq);
	return ((t_vec3){a.x * inv_mag, a.y * inv_mag, a.z * inv_mag, 0.0});
}
