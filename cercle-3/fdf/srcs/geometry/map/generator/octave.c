/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octave.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:17:25 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:21:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

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
