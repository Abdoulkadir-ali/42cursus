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

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w});
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w});
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w});
}
#endif

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