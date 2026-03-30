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

#include "surface.h"

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
	int		xi;
	int		yi;
	double	wx;
	double	wy;
	t_vec3	top;
	t_vec3	bot;

	fx = u * tex->width - 0.5;
	fy = v * tex->height - 0.5;
	xi = (int)fx;
	if (fx < 0.0 && (double)xi != fx)
		xi--;
	yi = (int)fy;
	if (fy < 0.0 && (double)yi != fy)
		yi--;
	wx = fx - (double)xi;
	wy = fy - (double)yi;
	top = vec3_add(vec3_scale(texel_at(tex, xi, yi), 1.0 - wx),
			vec3_scale(texel_at(tex, xi + 1, yi), wx));
	bot = vec3_add(vec3_scale(texel_at(tex, xi, yi + 1), 1.0 - wx),
			vec3_scale(texel_at(tex, xi + 1, yi + 1), wx));
	return (vec3_add(vec3_scale(top, 1.0 - wy), vec3_scale(bot, wy)));
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
	if (tex->type == TEX_BITMAP && tex->addr)
		return (sample_bitmap(tex, u, v));
	return (vec3(255, 0, 255));
}
