/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 13:42:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static t_vec3	sample_checker(t_texture *tex, double u, double v)
{
	int	ch;

	ch = (int)(floor(u * tex->scale) + floor(v * tex->scale)) % 2;
	if ((u * tex->scale) < 0)
		ch++;
	if ((v * tex->scale) < 0)
		ch++;
	if (ch % 2)
		return (tex->color_a);
	return (tex->color_b);
}

static t_vec3	texel_at(t_texture *tex, int x, int y)
{
	char			*px;
	unsigned int	cl;

	x = x % tex->width;
	if (x < 0)
		x += tex->width;
	y = y % tex->height;
	if (y < 0)
		y += tex->height;
	px = tex->addr + (y * tex->len + x * (tex->bpp / 8));
	cl = *(unsigned int *)px;
	return (vec3((cl >> 16) & 0xFF, (cl >> 8) & 0xFF, cl & 0xFF));
}

static t_vec3	sample_bitmap(t_texture *tex, double u, double v)
{
	double	fx;
	double	fy;
	t_vec3	top;
	t_vec3	bot;

	fx = u * tex->width - 0.5;
	fy = v * tex->height - 0.5;
	top = vec3_add(
			vec3_scale(texel_at(tex, (int)floor(fx), (int)floor(fy)),
				1.0 - (fx - floor(fx))),
			vec3_scale(texel_at(tex, (int)floor(fx) + 1, (int)floor(fy)),
				fx - floor(fx)));
	bot = vec3_add(
			vec3_scale(texel_at(tex, (int)floor(fx), (int)floor(fy) + 1),
				1.0 - (fx - floor(fx))),
			vec3_scale(texel_at(tex, (int)floor(fx) + 1, (int)floor(fy) + 1),
				fx - floor(fx)));
	return (vec3_add(vec3_scale(top, 1.0 - (fy - floor(fy))),
			vec3_scale(bot, fy - floor(fy))));
}

/*
** Samples a color from a texture (Solid, Checker, or Bitmap).
*/
t_vec3	sample_texture(t_texture *tex, double u, double v)
{
	if (tex->type == TEX_SOLID)
		return (tex->color_a);
	if (tex->type == TEX_CHECKER)
		return (sample_checker(tex, u, v));
	if (tex->type == TEX_BITMAP && tex->img)
		return (sample_bitmap(tex, u, v));
	return (vec3(255, 0, 255));
}
