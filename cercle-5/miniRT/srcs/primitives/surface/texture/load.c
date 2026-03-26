/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:30:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "surface.h"
#include "scene.h"
#include "stb.h"

/**
 * @brief Loads an XPM texture from disk via MLX.
 * @param scene Pointer to the scene.
 * @param tex Pointer to the texture.
 * @param path File path.
 * @return true on success, false on failure.
 */
static bool	load_xpm(t_scene *scene, t_texture *tex, const char *path)
{
	void	*img;
	int		w[2];

	if (!scene || !scene->mlx)
		return (false);
	img = mlx_xpm_file_to_image(scene->mlx, (char *)path, &w[0], &w[1]);
	if (!img)
		return (false);
	tex->img = img;
	tex->width = w[0];
	tex->height = w[1];
	tex->addr = mlx_get_data_addr(img, &tex->bpp, &tex->len, &tex->endian);
	tex->type = TEX_BITMAP;
	tex->scale = TEX_DEFAULT_SCALE;
	tex->color_a = get_colors()->white;
	return (true);
}

/**
 * @brief Standard entry point to load a texture from disk.
 * @param scene Pointer to the scene.
 * @param tex Pointer to the target texture.
 * @param path Path to the file.
 * @return true on success.
 */
bool	load_texture(t_scene *scene, t_texture *tex, const char *path)
{
	if (load_xpm(scene, tex, path))
		return (true);
	if (load_stbi(tex, path))
		return (true);
	return (false);
}

/**
 * @brief Loads a JPEG/PNG/BMP texture via internal stb_image.
 * @param tex Pointer to the texture.
 * @param path File path.
 * @return true on success, false on failure.
 */
bool	load_stbi(t_texture *tex, const char *path)
{
	int				w;
	int				h;
	int				ch;
	unsigned char	*data;

	stbi_set_flip_vertically_on_load(1);
	data = stbi_load(path, &w, &h, &ch, TEX_CH_RGBA);
	if (!data)
		return (false);
	convert_rgba_to_bgra(data, w * h * TEX_CH_RGBA);
	init_texture_props(tex, w, h, (char *)data);
	return (true);
}

/**
 * @brief Loads a texture from an in-memory buffer via stb_image.
 * @param tex Pointer to the texture.
 * @param buffer Pointer to the raw buffer.
 * @param size Buffer size in bytes.
 * @return true on success.
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
	data = stbi_load_from_memory(buffer, size, &w, &h, &ch, TEX_CH_RGBA);
	if (!data)
		return (false);
	convert_rgba_to_bgra(data, w * h * TEX_CH_RGBA);
	init_texture_props(tex, w, h, (char *)data);
	return (true);
}
