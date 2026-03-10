/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:45:43 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

double	sqrt(double x);

/**
 * @brief Compute the Euclidean length of a 3D integer vector.
 * @param v Vector to measure.
 * @return Length as a floating-point value.
 */
double	vec3_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * @brief Return the smallest component of a 3D integer vector.
 * @param v Vector to inspect.
 * @return Minimum among `x`, `y`, and `z`.
 */
double	vec3_min(t_vec3 v)
{
	double	min;

	min = v.x;
	if (v.y < min)
		min = v.y;
	if (v.z < min)
		min = v.z;
	return (min);
}

/**
 * @brief Return the largest component of a 3D integer vector.
 * @param v Vector to inspect.
 * @return Maximum among `x`, `y`, and `z`.
 */
double	vec3_max(t_vec3 v)
{
	double	max;

	max = v.x;
	if (v.y > max)
		max = v.y;
	if (v.z > max)
		max = v.z;
	return (max);
}

/**
 * @brief Return the component range of a 3D integer vector.
 * @param v Vector to inspect.
 * @return `t_vec2` storing `(min, max)`.
 */
t_vec2	vec3_get_minmax_components(t_vec3 v)
{
	return (create_vec2(vec3_min(v), vec3_max(v)));
}
