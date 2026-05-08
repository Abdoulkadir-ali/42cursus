/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:07:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 01:51:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "texture.h"

static unsigned int	get_pixel_color(t_xpm *xpm, unsigned int key)
{
	unsigned int	probe;

	if (!xpm->table)
		return (0);
	probe = (key * XPM_HASH_MULT) & (xpm->table_size - 1);
	while (xpm->table[probe].idx != 0)
	{
		if (xpm->table[probe].key == key)
			return (xpm->colors[xpm->table[probe].idx - 1].color);
		probe = (probe + 1) & (xpm->table_size - 1);
	}
	return (0);
}

static char	*xpm_get_next_line(t_parser *p)
{
	char	*line;

	while (parser_read_line_alloc(p, &line))
	{
		if (line[0] == '"')
			return (line);
		free(line);
	}
	return (NULL);
}

static int	parse_xpm_pixels(t_xpm *xpm)
{
	char	*line;
	t_vec2s	pos;

	pos.y = 0;
	while (pos.y < xpm->tex->size.y)
	{
		line = xpm_get_next_line(xpm->parser);
		if (!line)
			return (0);
		pos.x = 0;
		while (pos.x < xpm->tex->size.x)
		{
			xpm->tex->data[pos.y * xpm->tex->size.x
				+ pos.x] = get_pixel_color(xpm, xpm_token_key(line + 1
						+ pos.x * xpm->cpp, xpm->cpp));
			pos.x++;
		}
		free(line);
		pos.y++;
	}
	return (1);
}

static int	xpm_load_data(t_xpm *xpm, const char *path, t_world *world)
{
	if (xpm_read_header(xpm) || !parse_xpm_palette(xpm) || xpm_init_table(xpm))
		return (parser_close(xpm->parser), free(xpm->parser), 0);
	xpm->tex->data = ft_calloc(xpm->tex->size.x * xpm->tex->size.y,
			sizeof(int));
	if (!xpm->tex->data)
		return (parser_close(xpm->parser), free(xpm->parser), 0);
	if (parse_xpm_pixels(xpm) == 0)
		return (parser_close(xpm->parser), free(xpm->parser),
			free(xpm->colors), free(xpm->table), free(xpm->tex->data), 0);
	if (world)
		tex_cache_add(&world->tex_cache, path, xpm->tex->data, xpm->tex->size);
	ft_print_debug("[XPM] Successfully loaded %s (%dx%d)", path,
		(int)xpm->tex->size.x, (int)xpm->tex->size.y);
	free(xpm->colors);
	free(xpm->table);
	parser_close(xpm->parser);
	return (free(xpm->parser), 1);
}

int	load_xpm_manual(t_texture *tex, const char *path, t_world *world)
{
	t_xpm			xpm;
	t_cached_tex	*cached;

	if (world)
	{
		cached = tex_cache_get(&world->tex_cache, path);
		if (cached)
		{
			tex->data = cached->data;
			tex->size = cached->size;
			return (1);
		}
	}
	ft_print_debug("[XPM] Loading %s...", path);
	ft_bzero(&xpm, sizeof(xpm));
	xpm.tex = tex;
	xpm.parser = malloc(sizeof(t_parser));
	if (!xpm.parser)
		safe_exit("out of memory loading texture: %s", NULL, 1, path);
	if (!parser_init(xpm.parser, path))
		safe_exit("cannot open texture file: %s", NULL, 1, path);
	if (!xpm_load_data(&xpm, path, world))
		safe_exit("failed to parse texture: %s", NULL, 1, path);
	return (1);
}
