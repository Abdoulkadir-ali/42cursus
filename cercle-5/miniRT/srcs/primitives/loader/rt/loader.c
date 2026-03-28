/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 06:32:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Phase 1: parse a single line into the staging buffer (no scene touch).
*/
static bool	parse_line(t_scene *scene, t_rt_buf *buf, t_parser *p)
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
	return (dispatch_scan(scene, buf, p, id));
}

/*
** Two-phase .rt loader:
**   Phase 1 — parse the entire file into a transient staging buffer.
**   Phase 2 — only if phase 1 fully succeeded, inject into the scene.
** If any parse error occurs the scene is left completely untouched.
*/
bool	rt_load(t_scene *scene, const char *path)
{
	t_parser	p;
	t_rt_buf	buf;
	size_t		sz;
	char		*file;
	bool		ok;

	file = fbx_read_file(path, &sz);
	if (!file)
		return (false);
	if (!rt_buf_init(&buf))
	{
		free(file);
		return (false);
	}
	parser_init_str(&p, file, sz);
	p.path = path;
	ok = true;
	while (!p.eof && ok)
	{
		if (!parse_line(scene, &buf, &p))
		{
			ft_printf("Scene parse error @ %s\n", path);
			ok = false;
		}
		if (parser_peek(&p) == '\n')
			parser_advance(&p);
	}
	if (ok)
		ok = rt_buf_inject(scene, &buf);
	rt_buf_free(&buf);
	free(file);
	return (ok);
}
