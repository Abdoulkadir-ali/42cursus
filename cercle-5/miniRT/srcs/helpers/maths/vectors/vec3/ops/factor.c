/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mul.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:00:51 by abdoali          ###   ########.fr       */
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
	double	mag;

	mag = vec3_mag(a);
	if (mag < 1e-12)
		return ((t_vec3){0, 0, 0, 0});
	return (vec3_scale(a, 1.0 / mag));
}

double	vec3_mag(t_vec3 a)
{
	return (sqrt(vec3_mag_sq(a)));
}
