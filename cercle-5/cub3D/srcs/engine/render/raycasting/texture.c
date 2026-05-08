/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:38:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	is_texture_path(char *path)
{
	return (ft_strnstr(path, ".dxpm", ft_strlen(path))
		|| ft_strnstr(path, ".xpm", ft_strlen(path)));
}

int	load_texture(t_texture *tex, char *path, t_world *world, t_app *app)
{
	if (!tex || !path)
		return (0);
	if (ft_strnstr(path, ".dxpm", ft_strlen(path)))
	{
		if (load_dxpm_manual(tex, path, NULL, world))
			return (1);
	}
	if (ft_strnstr(path, ".xpm", ft_strlen(path)))
	{
		if (load_xpm_manual(tex, path, world))
			return (1);
	}
	if (is_texture_path(path))
		safe_exit("could not load texture: %s", app, 1, path);
	return (0);
}

t_vec3	get_tex_color(t_texture *tex, t_vec2i pos)
{
	unsigned int	p;
	t_vec3			color;

	if (!tex->data)
		return ((t_vec3){200.0f, 200.0f, 200.0f});
	pos.x = ((pos.x % tex->size.x) + tex->size.x) % tex->size.x;
	pos.y = ((pos.y % tex->size.y) + tex->size.y) % tex->size.y;
	p = tex->data[pos.y * tex->size.x + pos.x];
	color.x = (float)((p >> 16) & 0xFF);
	color.y = (float)((p >> 8) & 0xFF);
	color.z = (float)(p & 0xFF);
	return (color);
}
