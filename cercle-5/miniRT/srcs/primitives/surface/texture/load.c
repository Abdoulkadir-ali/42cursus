/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:18:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"
#include "scene.h"
#include "stb.h"
#include "debug.h"

static void	rb_swap_inplace(unsigned char *data, int count)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	while (i < count)
	{
		tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
		i += 4;
	}
}

bool	load_stbi(t_texture *tex, const char *path)
{
	int				w;
	int				h;
	int				ch;
	unsigned char	*data;

	DBG_TRACE_MSG(DBG_CH_TEXTURE, "load_stbi: loading '%s'\n", path);
	stbi_set_flip_vertically_on_load(1);
	data = stbi_load(path, &w, &h, &ch, 4);
	if (!data)
	{
		DBG_ERR_MSG(DBG_CH_TEXTURE, "load_stbi: stbi_load FAILED '%s'\n", path);
		return (false);
	}
	rb_swap_inplace(data, w * h * 4);
	init_texture_props(tex, w, h, (unsigned char *)data);
	DBG_INFO_MSG(DBG_CH_TEXTURE, "load_stbi OK: '%s' %dx%d\n", path, w, h);
	return (true);
}

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
		DBG_ERR_MSG(DBG_CH_TEXTURE, "load_texture_from_memory: stbi FAILED size=%d\n", size);
		return (false);
	}
	rb_swap_inplace(data, w * h * 4);
	init_texture_props(tex, w, h, (unsigned char *)data);
	DBG_INFO_MSG(DBG_CH_TEXTURE, "load_texture_from_memory OK: %dx%d\n", w, h);
	return (true);
}

bool	load_texture(t_scene *scene, t_texture *tex, const char *path)
{
	DBG_TRACE_MSG(DBG_CH_TEXTURE, "load_texture: '%s'\n", path);
	(void)scene;
	return (load_stbi(tex, path));
}
