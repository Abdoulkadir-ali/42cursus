/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:10:00 by abdoali          ###   ########.fr       */
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

static bool	ascii_build_mesh_local(t_fbx_ascii_ctx *ctx)
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
	return (true);
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

static void	fbx_ascii_load_materials(t_fbx_ascii_ctx *ctx, t_raw_model *out)
{
	char	*tex_path;
	int		mat_idx;

	tex_path = fbx_ascii_parse_texture_path(ctx->p, ctx->end, ctx->path);
	if (tex_path)
	{
		mat_idx = raw_model_add_material(out, "FBX_Material");
		if (mat_idx >= 0)
			raw_material_set_texture(&out->materials[mat_idx], tex_path);
		free(tex_path);
		if (out->mesh_count > 0)
		{
			out->mesh_mat_indices = malloc(sizeof(int) * out->mesh_count);
			if (out->mesh_mat_indices)
				out->mesh_mat_indices[0] = mat_idx;
		}
	}
}

bool	fbx_load_ascii(const char *path, t_raw_model *out)
{
	t_fbx_ascii_ctx	ctx;

	ft_memset(out, 0, sizeof(*out));
	if (!setup_ctx(&ctx, path))
		return (false);
	if (ascii_parse_mesh(&ctx) && ascii_build_mesh_local(&ctx))
	{
		out->meshes = malloc(sizeof(t_mesh));
		if (out->meshes)
		{
			out->meshes[0] = ctx.mesh.base;
			out->mesh_count = 1;
			fbx_ascii_load_materials(&ctx, out);
		}
	}
	free(ctx.buf);
	return (out->mesh_count > 0);
}
