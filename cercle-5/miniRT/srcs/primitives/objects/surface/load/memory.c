/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:24:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"

/*
** Loads a texture from a memory buffer via stb_image.
*/
bool	load_texture_from_memory(t_texture *tex, unsigned char *buffer,
			int size)
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
