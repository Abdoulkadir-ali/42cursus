/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:12:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

/**
 * @brief Apply the Perlin fade curve.
 * @param t Input interpolation value.
 * @return Smoothed interpolation factor.
 */
float	fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

/**
 * @brief Interpolate linearly between two scalars.
 * @param t Interpolation factor.
 * @param a First value.
 * @param b Second value.
 * @return Interpolated scalar value.
 */
float	lerp(float t, float a, float b)
{
	return (a + t * (b - a));
}

/**
 * @brief Interpolate linearly between two 2D vectors.
 * @param t Interpolation factor.
 * @param a First vector.
 * @param b Second vector.
 * @return Interpolated vector.
 */
t_vec2d	lerp_vec(float t, t_vec2d a, t_vec2d b)
{
	t_vec2d	result;

	result.x = a.x + t * (b.x - a.x);
	result.y = a.y + t * (b.y - a.y);
	return (result);
}

/**
 * @brief Compute the dot product with one gradient vector.
 * @param state Noise state containing precomputed gradients.
 * @param hash Gradient hash value.
 * @param x Local x offset.
 * @param y Local y offset.
 * @return Gradient contribution at the sample point.
 */
float	grad(t_noise_state *state, int hash, float x, float y)
{
	int		h;
	t_vec2d	g;

	h = hash & 255;
	g = state->grads[h];
	return (g.x * x + g.y * y);
}
