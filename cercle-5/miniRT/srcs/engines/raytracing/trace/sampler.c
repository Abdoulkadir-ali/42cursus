/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:40:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD Unified Texture Sampler.
 * Replaces the old Scene-based sampler with direct RAM-fetch lookups.
 * @param ctx Shading context containing the texture pool pointers.
 * @param idx Index of the texture in the engine's pool.
 * @param u/v Normalized coordinates.
 */
t_vec3	sample_texture_pool(t_shading *sha, int idx, double u, double v)
{
	unsigned char	*pix;
	t_vec2i			d;
	int				x;
	int				y;
	int				p;

	if (idx < 0 || !ctx->texture_pool || !ctx->texture_pool[idx])
		return (vec3(1, 0, 1)); /* Magenta Error */
	d = ctx->texture_dims[idx];
	x = (int)(u * (double)d.x) % d.x;
	y = (int)(v * (double)d.y) % d.y;
	if (x < 0) x += d.x;
	if (y < 0) y += d.y;
	p = (y * d.x + x) * 4;
	pix = ctx->texture_pool[idx];
	return (vec3(pix[p] / 255.0, pix[p + 1] / 255.0, pix[p + 2] / 255.0));
}
