/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 00:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Logic for handling individual scene-file lines.
 */
static bool	parse_line(t_scene *scene, t_parser *p)
{
	char	id[32];

	parser_skip_spaces(p);
	if (parser_peek(p) == '#' || parser_peek(p) == '\n')
	{
		while (parser_peek(p) && parser_peek(p) != '\n')
			parser_advance(p);
		return (true);
	}
	if (!parser_get_next_word(p, id, 32))
		return (true);
	return (dispatch_scan(scene, p, id));
}

/**
 * @brief Core entry point for loading MiniRT scene files (.rt).
 */
bool	rt_load(t_scene *scene, const char *path)
{
	t_parser	p;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	parser_init(&p, fd);
	p.path = path;
	while (!p.eof)
	{
		if (!parse_line(scene, &p))
			ft_printf("Scene error @ %s\n", path);
		if (parser_peek(&p) == '\n')
			parser_advance(&p);
	}
	close(fd);
	return (true);
}
