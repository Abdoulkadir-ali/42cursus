/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 04:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

/**
 * @brief Fetches a single RGB texel from raw texture address.
 * @param tex Pointer to the bitmap texture.
 * @param x Pixel X coordinate.
 * @param y Pixel Y coordinate.
 * @return t_vec3 The RGB color of the pixel.
 */
t_vec3	texel_at(t_texture *tex, int x, int y)
{
	char			*px;
	unsigned int	cl;

	x = x % tex->width;
	if (x < 0)
		x += tex->width;
	y = y % tex->height;
	if (y < 0)
		y += tex->height;
	px = tex->addr + (y * tex->len + x * (tex->bpp / BITS_PER_BYTE));
	cl = *(unsigned int *)px;
	return (vec3((cl >> 16) & 0xFF, (cl >> 8) & 0xFF, cl & 0xFF));
}
