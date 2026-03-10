/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:28:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

double	sqrt(double x);

/**
 * @brief Compute the Euclidean length of a 2D double vector.
 * @param v Vector to measure.
 * @return Double-precision vector length.
 */
double	vec2d_len(t_vec2d v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

/**
 * @brief Return the smaller component of a 2D double vector.
 * @param v Vector to inspect.
 * @return Minimum of `x` and `y`.
 */
double	vec2d_min(t_vec2d v)
{
	if (v.x < v.y)
		return (v.x);
	else
		return (v.y);
}

/**
 * @brief Return the larger component of a 2D double vector.
 * @param v Vector to inspect.
 * @return Maximum of `x` and `y`.
 */
double	vec2d_max(t_vec2d v)
{
	if (v.x > v.y)
		return (v.x);
	else
		return (v.y);
}

/**
 * @brief Pack a minimum and maximum value into one `t_vec2d`.
 * @param min Minimum value.
 * @param max Maximum value.
 * @return Vector storing `(min, max)`.
 */
t_vec2d	vec2d_minmax(int min, int max)
{
	return (create_vec2d(min, max));
}
