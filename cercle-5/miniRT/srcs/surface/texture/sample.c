/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:28:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

/**
 * @brief Master dispatcher for texture sampling.
 * @param tex Pointer to the texture struct.
 * @param u Horizontal coordinate [0..1].
 * @param v Vertical coordinate [0..1].
 * @return t_vec3 The sampled color.
 */
t_vec3	sample_texture(t_texture *tex, double u, double v)
{
	const t_colors *colors;
	
	colors = get_colors();
	if (!tex)
		return (colors->black);
	if (tex->type == TEX_SOLID)
		return (tex->color_a);
	if (tex->type == TEX_CHECKER)
		return (sample_checker(tex, u, v));
	if (tex->type == TEX_BITMAP && tex->addr)
		return (sample_bitmap(tex, u, v));
	return (colors->magenta);
}

/**
 * @brief Procedural checkerboard sampler.
 * @param tex Pointer to the checker texture.
 * @param u Horizontal UV coordinate [0..1].
 * @param v Vertical UV coordinate [0..1].
 * @return t_vec3 The dark or light color.
 */
t_vec3	sample_checker(t_texture *tex, double u, double v)
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
