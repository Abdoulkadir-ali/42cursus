/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 02:20:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:25:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3i	vec3i(int x, int y, int z)
{
	return ((t_vec3i){x, y, z});
}

t_vec3i	vec3i_add(t_vec3i a, t_vec3i b)
{
	return ((t_vec3i){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3i	vec3i_sub(t_vec3i a, t_vec3i b)
{
	return ((t_vec3i){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3i	vec3i_mul(t_vec3i a, t_vec3i b)
{
	return ((t_vec3i){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vec3i	vec3i_div(t_vec3i a, t_vec3i b)
{
	if (b.x == 0 || b.y == 0 || b.z == 0)
		return (a);
	return ((t_vec3i){a.x / b.x, a.y / b.y, a.z / b.z});
}
