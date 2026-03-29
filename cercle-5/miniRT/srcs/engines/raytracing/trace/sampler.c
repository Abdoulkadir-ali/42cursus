/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:00:23 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	get_pixel(unsigned char *pix, int px, int py, int w)
{
	int	p;

	p = (py * w + px) * 4;
	return (vec3(pix[p] / COLOR_MAX, pix[p + 1] / COLOR_MAX,
			pix[p + 2] / COLOR_MAX));
}

t_vec3	sample_texture_pool(t_shading *sha, int idx, double u, double v)
{
	unsigned char	*pxl;
	t_vec2i			d;
	t_bilinear		b;
	t_vec3			c[4];

	if (idx < 0 || !sha->rt->texture_pool || !sha->rt->texture_pool[idx])
		return (vec3(1, 0, 1));
	d = sha->rt->texture_dims[idx];
	pxl = sha->rt->texture_pool[idx];
	b.ux = u * (double)d.x - 0.5;
	b.uy = v * (double)d.y - 0.5;
	b.xi = (int)floor(b.ux);
	b.yi = (int)floor(b.uy);
	b.wx = b.ux - (double)b.xi;
	b.wy = b.uy - (double)b.yi;
	b.xi = (b.xi % d.x + d.x) % d.x;
	b.yi = (b.yi % d.y + d.y) % d.y;
	c[0] = get_pixel(pxl, b.xi, b.yi, d.x);
	c[1] = get_pixel(pxl, (b.xi + 1) % d.x, b.yi, d.x);
	c[2] = get_pixel(pxl, b.xi, (b.yi + 1) % d.y, d.x);
	c[3] = get_pixel(pxl, (b.xi + 1) % d.x, (b.yi + 1) % d.y, d.x);
	return (vec3_add(vec3_scale(vec3_add(vec3_scale(c[0], 1.0 - b.wx),
					vec3_scale(c[1], b.wx)), 1.0 - b.wy),
			vec3_scale(vec3_add(vec3_scale(c[2], 1.0 - b.wx),
					vec3_scale(c[3], b.wx)), b.wy)));
}
