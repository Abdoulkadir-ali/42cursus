/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:45:43 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:11:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

double	vec3d_len(t_vec3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec3d_min(t_vec3d v)
{
	double	min;

	min = v.x;
	if (v.y < min)
		min = v.y;
	if (v.z < min)
		min = v.z;
	return (min);
}

double	vec3d_max(t_vec3d v)
{
	double	max;

	max = v.x;
	if (v.y > max)
		max = v.y;
	if (v.z > max)
		max = v.z;
	return (max);
}

t_vec2d	vec3d_minmax(t_vec3d v)
{
	return (create_vec2d(vec3d_min(v), vec3d_max(v)));
}
