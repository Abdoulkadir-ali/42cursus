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

/**
 * @brief Compute the Euclidean length of a 2D integer vector.
 * @param v Vector to measure.
 * @return Integer length truncated from the square root result.
 */
int	vec2_len(t_vec2 v)
{
	return ((int)sqrt(v.x * v.x + v.y * v.y));
}

/**
 * @brief Return the smaller component of a 2D integer vector.
 * @param v Vector to inspect.
 * @return Minimum of `x` and `y`.
 */
int	vec2_min(t_vec2 v)
{
	if (v.x < v.y)
		return (v.x);
	return (v.y);
}

/**
 * @brief Return the larger component of a 2D integer vector.
 * @param v Vector to inspect.
 * @return Maximum of `x` and `y`.
 */
int	vec2_max(t_vec2 v)
{
	if (v.x > v.y)
		return (v.x);
	return (v.y);
}

/**
 * @brief Pack a minimum and maximum integer into one `t_vec2`.
 * @param min Minimum value.
 * @param max Maximum value.
 * @return Vector storing `(min, max)`.
 */
t_vec2	vec2_minmax(int min, int max)
{
	return (create_vec2(min, max));
}
