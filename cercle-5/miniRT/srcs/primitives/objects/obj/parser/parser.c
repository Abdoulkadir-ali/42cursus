/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	init_ctx(t_obj_ctx *ctx)
{
	ft_memset(ctx, 0, sizeof(t_obj_ctx));
	ctx->current_mat_id = -1;
	ctx->first_mtl_id = -1;
	ctx->bbox = aabb_create_empty();
}

static void	handle_id(t_obj_ctx *ctx, t_parser *p, t_scene *scene,
		const char *path)
{
	char	id[16];

	if (!obj_read_id(p, id, sizeof(id)))
		return ;
	if (ft_strcmp(id, "v") == 0)
		obj_parse_v(ctx, p);
	else if (ft_strcmp(id, "vt") == 0)
		obj_parse_vt(ctx, p);
	else if (ft_strcmp(id, "vn") == 0)
		obj_parse_vn(ctx, p);
	else if (ft_strcmp(id, "f") == 0)
		obj_parse_f(ctx, p);
	else if (ft_strcmp(id, "mtllib") == 0)
		obj_parse_mtllib(ctx, p, scene, path);
	else if (ft_strcmp(id, "usemtl") == 0)
		obj_parse_usemtl(ctx, p, scene);
}

bool	parse_obj(const char *path, t_scene *scene)
{
	t_parser	p;
	t_obj_ctx	ctx;
	int			fd;

	init_ctx(&ctx);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	parser_init(&p, fd);
	while (true)
	{
		parser_skip_spaces(&p);
		if (p.eof && p.cursor >= p.bytes_read)
			break ;
		if (parser_peek(&p) == '#')
		{
			obj_skip_line(&p);
			continue ;
		}
		handle_id(&ctx, &p, scene, path);
		obj_skip_line(&p);
	}
	close(fd);
	return (obj_build_mesh(scene, &ctx, path));
}
