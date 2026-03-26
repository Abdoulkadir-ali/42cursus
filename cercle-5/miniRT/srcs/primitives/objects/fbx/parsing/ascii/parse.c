/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	ascii_parse_mesh(t_fbx_ascii_ctx *ctx)
{
	char	*temp;

	temp = find_node(ctx->p, ctx->end, "Vertices:");
	if (!temp)
		return (false);
	temp = advance_to_data(temp, ctx->end);
	ctx->mesh.base.vertices = parse_array(&temp, &ctx->vc, sizeof(t_vec3),
			f_vec3);
	if (!ctx->mesh.base.vertices)
		return (false);
	temp = find_node(ctx->p, ctx->end, "PolygonVertexIndex:");
	if (!temp)
		return (false);
	temp = advance_to_data(temp, ctx->end);
	ctx->ri = parse_array(&temp, &ctx->rc, sizeof(int), f_int);
	if (!ctx->ri)
		return (false);
	ascii_load_normals(ctx);
	ascii_load_uvs(ctx);
	return (true);
}

static bool	ascii_build_mesh(t_fbx_ascii_ctx *ctx, t_scene *scene,
		const char *path)
{
	t_fbx_flat_args	p;

	p.raw = ctx->ri;
	p.raw_c = ctx->rc;
	p.n = ctx->rn;
	p.nc = ctx->nc;
	p.u = ctx->ru;
	p.uc = ctx->uc;
	p.vc = ctx->vc;
	fbx_build_flat(&ctx->mesh.base, &p);
	if (ctx->mesh.base.tri_count == 0)
		return (false);
	mesh_build_bvh(&ctx->mesh.base);
	ctx->mat_id = parse_texture(ctx->p, ctx->end, scene, path);
	if (ctx->mat_id >= 0)
		ctx->mesh.base.mat_id = ctx->mat_id;
	return (true);
}

static bool	parse_fbx_ascii_internal(t_fbx_ascii_ctx *ctx, t_scene *scene,
		const char *path)
{
	if (!ascii_parse_mesh(ctx))
		return (false);
	if (!ascii_build_mesh(ctx, scene, path))
		return (false);
	ft_print_debug("FBX ASCII Loaded: %s (%d tris)\n", path,
		ctx->mesh.base.tri_count);
	return (scene_add_animated(scene, ctx->mesh));
}

static bool	setup_ctx(t_fbx_ascii_ctx *ctx, const char *path)
{
	size_t	size;

	ft_memset(ctx, 0, sizeof(*ctx));
	ctx->path = path;
	ctx->buf = read_file_content(path, &size);
	if (!ctx->buf)
		return (false);
	ctx->p = ctx->buf;
	ctx->end = ctx->buf + size;
	ft_memset(&ctx->mesh, 0, sizeof(t_skinned_mesh));
	ctx->mesh.base.name = ft_strdup(path);
	if (!ctx->mesh.base.name)
	{
		free(ctx->buf);
		return (false);
	}
	return (true);
}

bool	parse_fbx_ascii(const char *path, t_scene *scene)
{
	t_fbx_ascii_ctx	ctx;

	ft_print_debug("DEBUG: parse_fbx_ascii starting for %s\n", path);
	if (!setup_ctx(&ctx, path))
		return (false);
	if (!parse_fbx_ascii_internal(&ctx, scene, path))
	{
		mesh_free(&ctx.mesh.base);
		free(ctx.buf);
		return (false);
	}
	free(ctx.buf);
	return (true);
}
