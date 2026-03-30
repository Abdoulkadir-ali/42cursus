/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:06:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:06:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

#ifndef VEC3_HOT_INLINE
t_vec3	vec3_scale(t_vec3 a, double s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s, a.w * s});
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x, 0.0});
}

double	vec3_mag_sq(t_vec3 a)
{
	return (vec3_dot(a, a));
}

double	vec3_mag(t_vec3 a)
{
	return (sqrt(vec3_mag_sq(a)));
}
#endif

t_vec3	vec3_reflect(t_vec3 I, t_vec3 N)
{
	return (vec3_sub(I, vec3_scale(N, 2 * vec3_dot(I, N))));
}

t_vec3	vec3_refract(t_vec3 I, t_vec3 N, double ior)
{
	double cosi = -fmax(-1.0, fmin(1.0, vec3_dot(I, N)));
	double etai = 1.0;
	double etat = ior;
	t_vec3 n = N;
	if (cosi < 0)
	{
		cosi = -cosi;
		n = vec3_scale(N, -1.0);
		double tmp = etai;
		etai = etat;
		etat = tmp;
	}
	double eta = etai / etat;
	double k = 1.0 - eta * eta * (1.0 - cosi * cosi);
	if (k < 0)
		return ((t_vec3){0, 0, 0, 0});
	return (vec3_add(vec3_scale(I, eta), vec3_scale(n, eta * cosi - sqrt(k))));
}