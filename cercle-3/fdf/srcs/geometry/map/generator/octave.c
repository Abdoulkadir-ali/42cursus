/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octave.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:17:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

/**
 * @brief Combine several Perlin octaves into one normalized sample.
 * @param x Normalized x coordinate.
 * @param y Normalized y coordinate.
 * @param p Generation parameters.
 * @param noise Initialized noise state.
 * @return Normalized octave noise value.
 */
float	get_octave_noise(float x, float y, t_gen_params p, t_noise_state *noise)
{
	float	total;
	float	frequency;
	float	amplitude;
	float	max_value;
	int		i;

	total = 0;
	frequency = 1;
	amplitude = 1;
	max_value = 0;
	i = 0;
	while (i < p.octaves)
	{
		total += perlin2d(noise, (t_vec2d){x * p.scale * frequency,
				y * p.scale * frequency}) * amplitude;
		max_value += amplitude;
		amplitude *= p.persistence;
		frequency *= 2;
		i++;
	}
	return ((total / max_value) + 0.5f);
}
