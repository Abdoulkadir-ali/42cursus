/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 06:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Samples a color from a texture (Solid, Checker, or Bitmap).
*/
t_vec3	sample_texture(t_texture *tex, double u, double v)
{
	int				ch;
	int				xy[2];
	char			*px;
	unsigned int	cl;

	if (tex->type == TEX_SOLID)
		return (tex->color_a);
	if (tex->type == TEX_CHECKER)
	{
		ch = (int)(floor(u * tex->scale) + floor(v * tex->scale)) % 2;
		if ((u * tex->scale) < 0)
			ch++;
		if ((v * tex->scale) < 0)
			ch++;
		if (ch % 2)
			return (tex->color_a);
		return (tex->color_b);
	}
	if (tex->type == TEX_BITMAP && tex->img)
	{
		xy[0] = ((int)(u * tex->width) % tex->width + tex->width) % tex->width;
		xy[1] = ((int)(v * tex->height) % tex->height + tex->height) % tex->height;
		px = tex->addr + (xy[1] * tex->len + xy[0] * (tex->bpp / 8));
		cl = *(unsigned int *)px;
		return (vec3((cl >> 16) & 0xFF, (cl >> 8) & 0xFF, cl & 0xFF));
	}
	return (vec3(255, 0, 255));
}
