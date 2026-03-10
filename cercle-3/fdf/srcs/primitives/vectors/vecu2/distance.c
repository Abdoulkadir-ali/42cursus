/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Compute the Euclidean length of a 2D unsigned vector.
 * @param v Vector to measure.
 * @return Length converted to `unsigned int`.
 */
unsigned int	vecu2_len(t_vecu2 v)
{
	return ((unsigned int)sqrt(v.x * v.x + v.y * v.y));
}

/**
 * @brief Return the smaller component of a 2D unsigned vector.
 * @param v Vector to inspect.
 * @return Minimum of `x` and `y`.
 */
unsigned int	vecu2_min(t_vecu2 v)
{
	if (v.x < v.y)
		return (v.x);
	return (v.y);
}

/**
 * @brief Return the larger component of a 2D unsigned vector.
 * @param v Vector to inspect.
 * @return Maximum of `x` and `y`.
 */
unsigned int	vecu2_max(t_vecu2 v)
{
	if (v.x > v.y)
		return (v.x);
	return (v.y);
}
