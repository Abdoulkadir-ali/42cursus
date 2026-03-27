/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 09:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	fbx_bin_free_data(t_fbx_bin_ctx *ctx)
{
	if (ctx->data.v)
		free(ctx->data.v);
	if (ctx->data.ri)
		free(ctx->data.ri);
	if (ctx->data.vn)
		free(ctx->data.vn);
	if (ctx->data.vu)
		free(ctx->data.vu);
}

static bool	fbx_bin_open(t_fbx_bin_ctx *ctx, const char *path)
{
	char	header[64];

	ctx->fd = open(path, O_RDONLY);
	if (ctx->fd < 0)
		return (false);
	if (read(ctx->fd, header, 23) < 23 || read(ctx->fd, &ctx->version, 4) < 4)
	{
		fprintf(stderr, "Error: Failed to read FBX binary header\n");
		close(ctx->fd);
		ctx->fd = -1;
		return (false);
	}
	ft_memset(&ctx->mesh, 0, sizeof(t_skinned_mesh));
	ft_memset(&ctx->data, 0, sizeof(t_fbx_data));
	ctx->mesh.base.name = ft_strdup(path);
	if (!ctx->mesh.base.name)
	{
		close(ctx->fd);
		ctx->fd = -1;
		return (false);
	}
	return (true);
}

static bool	fbx_bin_parse(t_fbx_bin_ctx *ctx)
{
	parse_nodes(ctx->fd, (uint64_t)-1, ctx->version >= 7500, &ctx->data);
	close(ctx->fd);
	ctx->fd = -1;
	if (!ctx->data.v || !ctx->data.ri)
		return (false);
	return (true);
}

bool	fbx_load_binary(const char *path, t_raw_model *out)
{
	t_fbx_bin_ctx	ctx;

	ft_memset(out, 0, sizeof(*out));
	if (!fbx_bin_open(&ctx, path))
		return (false);
	if (!fbx_bin_parse(&ctx) || !fbx_bin_build_mesh(&ctx))
	{
		fbx_bin_free_data(&ctx);
		free(ctx.mesh.base.name);
		return (false);
	}
	out->meshes = malloc(sizeof(t_mesh));
	if (out->meshes)
	{
		out->meshes[0] = ctx.mesh.base;
		out->mesh_count = 1;
	}
	return (out->mesh_count > 0);
}
