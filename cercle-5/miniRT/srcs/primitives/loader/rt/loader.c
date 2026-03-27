/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 01:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Dispatch logic for single-pass memory-backed parsing.
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
 * @brief Bulk-reading entry point for loading MiniRT scene files (.rt).
 * Reads the whole file into a buffer before processing for 100% DOD compliance.
 */
bool	rt_load(t_scene *scene, const char *path)
{
	t_parser	p;
	size_t		sz;
	char		*buf;

	buf = fbx_read_file(path, &sz);
	if (buf == NULL)
		return (false);
	/* Initialize parser with full buffer (Self-contained bulk process) */
	/* Here we use a fake fd strategy or custom parser logic */
	/* For simplicity, we adapt existing parser to walk the buffer */
	parser_init_str(&p, buf, sz);
	p.path = path;
	while (!p.eof)
	{
		if (!parse_line(scene, &p))
			ft_printf("Scene error @ %s\n", path);
		if (parser_peek(&p) == '\n')
			parser_advance(&p);
	}
	free(buf);
	return (true);
}
