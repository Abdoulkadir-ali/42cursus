/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:24:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"

/*
** Loads an XPM texture from disk via mlx.
** Returns true on success, false on failure.
*/
bool	load_xpm(void *mlx_ptr, t_texture *tex, const char *path)
{
	if (!mlx_ptr)
		return (false);
	tex->img = mlx_xpm_file_to_image(mlx_ptr, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (false);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->len, &tex->endian);
	tex->type = TEX_BITMAP;
	tex->scale = 1.0;
	tex->color_a = vec3(255, 255, 255);
	return (true);
}
