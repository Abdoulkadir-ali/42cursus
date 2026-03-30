/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

/*
** Converts RGBA to BGRA format for mlx compatibility.
*/
void	convert_rgba_to_bgra(unsigned char *data, int size)
{
	unsigned char	tmp;
	int				i;

	i = 0;
	while (i < size)
	{
		tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
		i += 4;
	}
}

/*
** Initializes texture properties from loaded image data.
*/
void	init_texture_props(t_texture *tex, int w, int h, char *data)
{
	tex->img = NULL;
	tex->width = w;
	tex->height = h;
	tex->bpp = 32;
	tex->len = w * 4;
	tex->endian = 0;
	tex->addr = data;
	tex->type = TEX_BITMAP;
	tex->scale = 1.0;
	tex->color_a = vec3(255, 255, 255);
}
