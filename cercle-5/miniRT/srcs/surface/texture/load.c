/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "mlx.h"

/*
** Loads an XPM texture from disk.
** Populates the t_texture struct with image data and dimensions.
** Returns true on success, false on failure.
*/
bool	load_texture_xpm(t_scene *scene, t_texture *tex, const char *path)
{
	void	*img;
	int		w;
	int		h;

	if (!scene || !scene->mlx)
	{
		fprintf(stderr, "Error: MLX not initialized for texture loading\n");
		return (false);
	}
	ft_print_debug("DEBUG: Loading texture %s\n", path);
	img = mlx_xpm_file_to_image(scene->mlx, (char *)path, &w, &h);
	if (!img)
	{
		fprintf(stderr, "Error: Failed to load XPM texture: %s\n", path);
		return (false);
	}
	tex->img = img;
	tex->width = w;
	tex->height = h;
	tex->addr = mlx_get_data_addr(img, &tex->bpp, &tex->len, &tex->endian);
	tex->type = TEX_BITMAP;
	tex->scale = 1.0;
	tex->color_a = vec3(255, 255, 255); /* Tint color if needed */
	return (true);
}
