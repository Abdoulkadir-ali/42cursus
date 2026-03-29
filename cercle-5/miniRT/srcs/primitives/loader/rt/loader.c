/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:39:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "debug.h"

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
	DBG_INFO_MSG(DBG_CH_PARSER, "rt_load: parsing %s (%zu bytes)\n", path, sz);
	if (!rt_buf_init(&buf))
	{
		free(file);
		return (false);
	}
	parser_init_str(&p, file, sz);
	p.path = path;
	ok = true;
	while (parser_peek(&p) && ok)
	{
		if (!parse_line(scene, &buf, &p))
		{
			ft_printf("Scene parse error @ %s\n", path);
			DBG_ERR_MSG(DBG_CH_PARSER,
				"Parse FAIL at cursor=%zu | buf shapes=%zu\n",
				p.cursor, buf.shape_count);
			ok = false;
		}
		if (parser_peek(&p) == '\n')
			parser_advance(&p);
	}
	if (ok)
		ok = rt_buf_inject(scene, &buf);
	rt_buf_free(&buf);
	free(file);
	if (ok)
		DBG_INFO_MSG(DBG_CH_PARSER,
			"rt_load OK: %s | prims=%zu tris=%zu mats=%zu\n",
			path, scene->primitives.count,
			scene->tri_soa.count, scene->mat_count);
	else
		DBG_ERR_MSG(DBG_CH_PARSER, "rt_load FAIL: %s\n", path);
	return (ok);
}
