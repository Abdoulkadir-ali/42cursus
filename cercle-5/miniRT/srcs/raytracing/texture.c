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

#include "material.h"
#include <math.h>

t_vec3	sample_texture(t_texture *tex, double u, double v)
{
	if (tex->type == TEX_SOLID)
		return (tex->color_a);
	
	if (tex->type == TEX_CHECKER)
	{
		// Scalable checker logic using UVs
		int check = (int)(floor(u * tex->scale) + floor(v * tex->scale)) % 2;
		// Handle negative UVs correctly
		if ((u * tex->scale) < 0) check++;
		if ((v * tex->scale) < 0) check++;
		check = check % 2;
		
		return (check ? tex->color_a : tex->color_b);
	}
	
	if (tex->type == TEX_BITMAP && tex->img)
	{
		int x = (int)(u * tex->width) % tex->width;
		int y = (int)(v * tex->height) % tex->height;
		
		if (x < 0) x += tex->width;
		if (y < 0) y += tex->height;
		
		char *pixel = tex->addr + (y * tex->len + x * (tex->bpp / 8));
		unsigned int color = *(unsigned int *)pixel;
		int r = (color >> 16) & 0xFF;
		int g = (color >> 8) & 0xFF;
		int b = color & 0xFF;
		return (vec3(r, g, b));
	}

	return (vec3(255, 0, 255)); // Error pink
}
