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

#include "objects.h"

static void	skip_comment(t_parser *p)
{
	while (parser_peek(p) && parser_peek(p) != '\n')
		parser_advance(p);
}

bool	rt_init_parser(t_rt_ctx *ctx, const char *path)
{
	ctx->status = true;
	ctx->fd = open(path, O_RDONLY);
	if (ctx->fd == -1)
	{
		fprintf(stderr, "Error: Could not open .rt file %s\n", path);
		return (false);
	}
	if (!ctx->parser)
		return (false);
	parser_init(ctx->parser, ctx->fd);
	return (true);
}

bool	rt_parse_loop(t_scene *scene, t_rt_ctx *ctx)
{
	while (true)
	{
		parser_skip_spaces(ctx->parser);
		if (ctx->parser->eof
			&& ctx->parser->cursor >= ctx->parser->bytes_read)
			break ;
		if (parser_peek(ctx->parser) == '#')
		{
			skip_comment(ctx->parser);
			continue ;
		}
		if (!rt_parse_entry(scene, ctx))
			break ;
	}
	return (ctx->status);
}
