/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	read_id(t_parser *p, char *buf, size_t max_len)
{
	size_t	i;
	char	c;

	parser_skip_spaces(p);
	i = 0;
	c = parser_peek(p);
	if (!c)
		return (false);
	while (c && !ft_isspace(c) && i < max_len - 1)
	{
		buf[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	buf[i] = '\0';
	return (i > 0);
}

static void	handle_unknown(t_parser *p)
{
	while (parser_peek(p) && parser_peek(p) != '\n')
		parser_advance(p);
}

bool	rt_parse_entry(t_scene *scene, t_rt_ctx *ctx)
{
	if (!read_id(ctx->parser, ctx->id, sizeof(ctx->id)))
		return (false);
	ctx->obj = dispatch_scan(ctx->parser, ctx->id);
	if (ctx->obj.type == TYPE_NONE)
	{
		handle_unknown(ctx->parser);
		ctx->status = false;
		return (true);
	}
	if (!process_object(scene, ctx->obj))
		ctx->status = false;
	return (true);
}
