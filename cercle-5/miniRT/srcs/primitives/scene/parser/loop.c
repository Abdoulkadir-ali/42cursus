/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	skip_comment(t_parser *p)
{
	while (parser_peek(p) && parser_peek(p) != '\n')
		parser_advance(p);
}

bool	rt_init_parser(t_rt *rt, const char *path)
{
	rt->status = true;
	rt->fd = open(path, O_RDONLY);
	if (rt->fd == -1)
	{
		fprintf(stderr, "Error: Could not open .rt file %s\n", path);
		return (false);
	}
	if (!rt->parser)
		return (false);
	parser_init(rt->parser, rt->fd);
	return (true);
}

bool	rt_parse_loop(t_scene *scene, t_rt *rt)
{
	rt->line_num = 1;
	while (true)
	{
		parser_skip_spaces(rt->parser);
		if (rt->parser->eof
			&& rt->parser->cursor >= rt->parser->bytes_read)
			break ;
		if (parser_peek(rt->parser) == '\n')
		{
			rt->line_num++;
			parser_advance(rt->parser);
			continue ;
		}
		if (parser_peek(rt->parser) == '#')
		{
			skip_comment(rt->parser);
			continue ;
		}
		if (!rt_parse_entry(scene, rt))
			break ;
	}
	return (rt->status);
}
