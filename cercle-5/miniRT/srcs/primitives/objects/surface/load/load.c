/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:24:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

/*
** Loads a texture from disk. Tries XPM first, then stb_image.
*/
bool	load_texture(void *mlx_ptr, t_texture *tex, const char *path)
{
	ft_print_debug("DEBUG: Loading texture %s\n", path);
	if (load_xpm(mlx_ptr, tex, path))
		return (true);
	if (load_stbi(tex, path))
		return (true);
	fprintf(stderr, "Error: Failed to load texture: %s\n", path);
	return (false);
}

/*
** Legacy wrapper kept for compatibility.
*/
bool	load_texture_xpm(void *mlx_ptr, t_texture *tex, const char *path)
{
	return (load_texture(mlx_ptr, tex, path));
}
