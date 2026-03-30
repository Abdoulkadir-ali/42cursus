/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 13:42:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

/*
** Loads an XPM texture from disk via mlx.
** Returns true on success, false on failure.
*/
static bool	load_xpm(t_scene *scene, t_texture *tex, const char *path)
{
	void	*img;
	int		w;
	int		h;

	if (!scene || !scene->mlx)
		return (false);
	img = mlx_xpm_file_to_image(scene->mlx, (char *)path, &w, &h);
	if (!img)
		return (false);
	tex->img = img;
	tex->width = w;
	tex->height = h;
	tex->addr = mlx_get_data_addr(img, &tex->bpp, &tex->len, &tex->endian);
	tex->type = TEX_BITMAP;
	tex->scale = 1.0;
	tex->color_a = vec3(255, 255, 255);
	return (true);
}

/*
** Loads a JPG/PNG/BMP texture via stb_image.
** Converts RGBA data into BGRA format matching mlx pixel layout.
*/
static bool	load_stbi(t_texture *tex, const char *path)
{
	int				w;
	int				h;
	int				ch;
	unsigned char	*data;

	stbi_set_flip_vertically_on_load(1);
	data = stbi_load(path, &w, &h, &ch, 4);
	if (!data)
	{
		ft_print_debug("Error: stbi_load failed: %s (path: %s)\n", 
			stbi_failure_reason(), path);
		return (false);
	}
	convert_rgba_to_bgra(data, w * h * 4);
	init_texture_props(tex, w, h, (char *)data);
	return (true);
}

/*
** Loads a texture from a memory buffer via stb_image.
*/
bool	load_texture_from_memory(t_texture *tex, unsigned char *buffer, int size)
{
	int				w;
	int				h;
	int				ch;
	unsigned char	*data;

	if (!buffer || size <= 0)
		return (false);
	stbi_set_flip_vertically_on_load(1);
	data = stbi_load_from_memory(buffer, size, &w, &h, &ch, 4);
	if (!data)
	{
		ft_print_debug("Error: stbi_load_from_memory failed: %s\n",
			stbi_failure_reason());
		return (false);
	}
	convert_rgba_to_bgra(data, w * h * 4);
	init_texture_props(tex, w, h, (char *)data);
	return (true);
}

/*
** Loads a texture from disk. Tries XPM first, then stb_image.
*/
bool	load_texture(t_scene *scene, t_texture *tex, const char *path)
{
	ft_print_debug("DEBUG: Loading texture %s\n", path);
	if (load_xpm(scene, tex, path))
		return (true);
	if (load_stbi(tex, path))
		return (true);
	fprintf(stderr, "Error: Failed to load texture: %s\n", path);
	return (false);
}

/*
** Legacy wrapper kept for compatibility.
*/
bool	load_texture_xpm(t_scene *scene, t_texture *tex, const char *path)
{
	return (load_texture(scene, tex, path));
}
