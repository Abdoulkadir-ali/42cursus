/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:01:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 20:01:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

#ifndef VEC3_HOT_INLINE

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y \
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
