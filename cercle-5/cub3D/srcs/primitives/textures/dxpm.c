/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dxpm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:08:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 01:51:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "texture.h"

static void	patch_pixel(t_xpm *xpm, t_vec2s pos, const char *token)
{
	unsigned int	key;
	unsigned int	probe;

	key = xpm_token_key(token, xpm->cpp);
	probe = (key * XPM_HASH_MULT) & (xpm->table_size - 1);
	while (xpm->table[probe].idx != 0)
	{
		if (xpm->table[probe].key == key)
		{
			xpm->tex->data[pos.y * xpm->tex->size.x
				+ pos.x] = xpm->colors[xpm->table[probe].idx - 1].color;
			return ;
		}
		probe = (probe + 1) & (xpm->table_size - 1);
	}
}

static char	*parse_dxpm_span(t_xpm *xpm, t_vec2s pos, char *p)
{
	int	len;
	int	x;

	pos.x = ft_atoi(p);
	while (*p && !ft_isspace(*p) && *p != ',')
		p++;
	p += (*p == ',');
	len = ft_atoi(p);
	while (*p && !ft_isspace(*p))
		p++;
	while (*p && ft_isspace(*p))
		p++;
	if (pos.y < xpm->tex->size.y)
	{
		x = 0;
		while (x < len && (pos.x + x) < xpm->tex->size.x)
		{
			patch_pixel(xpm, (t_vec2s){pos.x + x, pos.y}, p);
			p += xpm->cpp;
			x++;
		}
	}
	while (*p && ft_isspace(*p))
		p++;
	return (p);
}

static void	parse_dxpm_rows(t_xpm *xpm)
{
	char	*line;
	char	*p;
	t_vec2s	pos;

	while (parser_read_line_alloc(xpm->parser, &line))
	{
		if (line[0] == 'R')
		{
			p = line + 1;
			pos.y = ft_atoi(p);
			while (*p && !ft_isspace(*p))
				p++;
			while (*p && ft_isspace(*p))
				p++;
			while (*p && *p != '\n' && *p != '\r')
				p = parse_dxpm_span(xpm, pos, p);
		}
		free(line);
	}
}

static int	dxpm_load_data(t_xpm *xpm, const char *path, unsigned int *prev,
		t_world *world)
{
	if (xpm_read_header(xpm))
		return (parser_close(xpm->parser), free(xpm->parser), 0);
	if (!parse_xpm_palette(xpm) || xpm_init_table(xpm))
		return (parser_close(xpm->parser), free(xpm->parser), 0);
	xpm->tex->data = ft_calloc(xpm->tex->size.x * xpm->tex->size.y,
			sizeof(int));
	if (!xpm->tex->data)
		return (free(xpm->colors), free(xpm->table), 0);
	ft_memcpy(xpm->tex->data, prev,
		xpm->tex->size.x * xpm->tex->size.y * sizeof(int));
	parse_dxpm_rows(xpm);
	if (world)
		tex_cache_add(&world->tex_cache, path, xpm->tex->data, xpm->tex->size);
	free(xpm->colors);
	free(xpm->table);
	parser_close(xpm->parser);
	return (free(xpm->parser), 1);
}

int	load_dxpm_manual(t_texture *tex, const char *path, unsigned int *prev,
		struct s_world *world)
{
	t_xpm			xpm;
	t_cached_tex	*cached;

	if (world)
	{
		cached = tex_cache_get(&((t_world *)world)->tex_cache, path);
		if (cached)
		{
			tex->data = cached->data;
			tex->size = cached->size;
			return (1);
		}
	}
	ft_bzero(&xpm, sizeof(xpm));
	xpm.tex = tex;
	xpm.parser = malloc(sizeof(t_parser));
	if (!prev)
		safe_exit("no base frame for delta texture: %s", NULL, 1, path);
	if (!xpm.parser)
		safe_exit("out of memory loading texture: %s", NULL, 1, path);
	if (!parser_init(xpm.parser, path))
		safe_exit("cannot open texture file: %s", NULL, 1, path);
	if (!dxpm_load_data(&xpm, path, prev, (t_world *)world))
		safe_exit("failed to parse texture: %s", NULL, 1, path);
	return (1);
}
