/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
/*
** Parses an already-open fd as an RT scene stream.
** The caller owns the fd and is responsible for closing it.
** Use this when the RT content lives in a pipe or memfd rather than a file.
*/
bool    parse_rt_fd(int fd, t_scene *scene)
{
        t_rt_ctx        ctx = {0};
        t_parser        parser = {0};

        ctx.parser = &parser;
        ctx.status = true;
        ctx.fd = fd;
        parser_init(ctx.parser, fd);
        rt_parse_loop(scene, &ctx);
        return (ctx.status);
}

bool	parse_rt(const char *path, t_scene *scene)
{
	t_rt_ctx	ctx = {0};
	t_parser	parser = {0};

	ctx.parser = &parser;
	if (!rt_init_parser(&ctx, path))
		return (false);
	rt_parse_loop(scene, &ctx);
	close(ctx.fd);
	return (ctx.status);
}
