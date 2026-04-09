/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:47:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:47:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3i	vec3i_add(t_vec3i a, t_vec3i b)
{
	return ((t_vec3i){a.x + b.x, a.y + b.y, a.z + b.z, 0});
}

t_vec3i	vec3i_sub(t_vec3i a, t_vec3i b)
{
	return ((t_vec3i){a.x - b.x, a.y - b.y, a.z - b.z, 0});
}

t_vec3i	vec3i_mul(t_vec3i a, t_vec3i b)
{
	return ((t_vec3i){a.x * b.x, a.y * b.y, a.z * b.z, 0});
}

t_vec3i	vec3i_scale(t_vec3i a, int s)
{
	return ((t_vec3i){a.x * s, a.y * s, a.z * s, 0});
}
