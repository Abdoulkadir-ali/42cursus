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

static int	wrap_coord(double v, int size)
{
	int	val;

	val = (int)(v * size) % size;
	if (val < 0)
		val += size;
	return (val);
}

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

static t_vec3	sample_bitmap(t_texture *tex, double u, double v)
{
	int				xy[2];
	char			*px;
	unsigned int	cl;

	xy[0] = wrap_coord(u, tex->width);
	xy[1] = wrap_coord(v, tex->height);
	px = tex->addr + (xy[1] * tex->len + xy[0] * (tex->bpp / 8));
	cl = *(unsigned int *)px;
	return (vec3((cl >> 16) & 0xFF, (cl >> 8) & 0xFF, cl & 0xFF));
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
