/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stbi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:24:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"

/*
** Loads a JPG/PNG/BMP texture via stb_image.
** Converts RGBA data into BGRA format matching mlx pixel layout.
*/
bool	load_stbi(t_texture *tex, const char *path)
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
