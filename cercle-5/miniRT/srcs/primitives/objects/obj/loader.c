/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 12:50:00 by abdoali          ###   ########.fr       */
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

static void	handle_id_raw(t_obj_ctx *ctx, t_parser *p, t_raw_model *model, const char *path)
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
		obj_parse_mtllib_raw(ctx, p, model, path);
	else if (ft_strcmp(id, "usemtl") == 0)
		obj_parse_usemtl_raw(ctx, p, model);
}

bool	obj_load(const char *path, t_raw_model *out)
{
	t_parser	p;
	t_obj_ctx	ctx;
	int			fd;

	init_ctx(&ctx);
	ft_memset(out, 0, sizeof(*out));
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
		handle_id_raw(&ctx, &p, out, path);
		obj_skip_line(&p);
	}
	close(fd);
	bool res = obj_finalize_mesh_raw(&ctx, out, path);
	return (res);
}
