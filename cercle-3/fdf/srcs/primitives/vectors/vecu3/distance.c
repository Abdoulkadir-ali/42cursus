/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Compute the Euclidean length of a 3D unsigned vector.
 * @param v Vector to measure.
 * @return Length converted to `unsigned int`.
 */
unsigned int	vecu3_len(t_vecu3 v)
{
	return ((unsigned int)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * @brief Return the smallest component of a 3D unsigned vector.
 * @param v Vector to inspect.
 * @return Minimum among `x`, `y`, and `z`.
 */
unsigned int	vecu3_min(t_vecu3 v)
{
	unsigned int	min;

	min = v.x;
	if (v.y < min)
		min = v.y;
	if (v.z < min)
		min = v.z;
	return (min);
}

/**
 * @brief Return the largest component of a 3D unsigned vector.
 * @param v Vector to inspect.
 * @return Maximum among `x`, `y`, and `z`.
 */
unsigned int	vecu3_max(t_vecu3 v)
{
	unsigned int	max;

	max = v.x;
	if (v.y > max)
		max = v.y;
	if (v.z > max)
		max = v.z;
	return (max);
}
