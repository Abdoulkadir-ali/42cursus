/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:29:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

/**
 * @brief Initializes texture metadata from raw data parameters.
 * @param tex Pointer to the texture.
 * @param w Width in pixels.
 * @param h Height in pixels.
 * @param data Pointer to the pixel data.
 */
void	init_texture_props(t_texture *tex, int w, int h, unsigned char *data)
{	
	tex->img = NULL;
	tex->width = w;
	tex->height = h;
	tex->bpp = TEX_DEFAULT_BPP;
	tex->len = w * TEX_CH_RGBA;
	tex->endian = 0;
	tex->addr = data;
	tex->type = TEX_BITMAP;
	tex->scale = TEX_DEFAULT_SCALE;
	tex->color_a = get_colors()->white;
	tex->pool_idx = -1;
	tex->bytes_per_pixel = TEX_CH_RGBA;
	tex->is_pow2 = (w > 0 && (w & (w - 1)) == 0) && (h > 0 && (h & (h - 1)) == 0);
}
