/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:47:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:47:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

int	vec3i_dot(t_vec3i a, t_vec3i b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3i	vec3i_cross(t_vec3i a, t_vec3i b)
{
	return ((t_vec3i){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x, 0});
}

int	vec3i_mag_sq(t_vec3i a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

int	vec3i_mag(t_vec3i a)
{
	return ((int)sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3i	vec3i_norm(t_vec3i a)
{
	int	m;

	m = vec3i_mag(a);
	if (m == 0)
		return ((t_vec3i){0, 0, 0, 0});
	return ((t_vec3i){a.x / m, a.y / m, a.z / m, 0});
}
