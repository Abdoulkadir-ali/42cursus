/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:00:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x, 0.0});
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_triple_product(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (vec3_sub(vec3_scale(b, vec3_dot(a, c)), vec3_scale(a, vec3_dot(b,
					c))));
}
