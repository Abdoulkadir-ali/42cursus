/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_sample.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 05:00:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"

static inline float	srgb_to_linear(float c)
{
	return (c * c);
}

static t_vec3	sample_checker(const t_texture *t, float u, float v)
{
	int	gx;
	int	gy;

	gx = (int)floorf(u * t->scale);
	gy = (int)floorf(v * t->scale);
	if (((gx ^ gy) & 1) == 0)
		return (t->color_a);
	return (t->color_b);
}

static t_vec3	sample_pixels(const t_texture *t, float u, float v, float lod)
{
	unsigned char	*pixels;
	int				level;
	t_vec2i			dim;
	t_vec2i			p;
	int				idx;

	level = (int)floorf(lod);
	if (level < 0)
		level = 0;
	if (level > t->n_mips)
		level = t->n_mips;
	if (level == 0)
	{
		dim = (t_vec2i){t->w, t->h};
		pixels = t->pixels;
	}
	else
	{
		dim = (t_vec2i){t->mips[level - 1].w, t->mips[level - 1].h};
		pixels = t->mips[level - 1].pixels;
	}
	p.x = (int)(u * dim.x);
	p.y = (int)(v * dim.y);
	if (p.x < 0) p.x = 0;
	if (p.x >= dim.x) p.x = dim.x - 1;
	if (p.y < 0) p.y = 0;
	if (p.y >= dim.y) p.y = dim.y - 1;
	idx = (p.y * dim.x + p.x) * 3;
	return (v3(srgb_to_linear(pixels[idx] / 255.0f),
			srgb_to_linear(pixels[idx + 1] / 255.0f),
			srgb_to_linear(pixels[idx + 2] / 255.0f)));
}

t_vec3	texture_sample(const t_texture *t, float u, float v, float lod)
{
	if (!t || t->kind == TEX_NONE)
		return (v3(1, 1, 1));
	if (t->kind == TEX_CHECKER)
		return (sample_checker(t, u, v));
	u -= floorf(u);
	v -= floorf(v);
	return (sample_pixels(t, u, v, lod));
}
