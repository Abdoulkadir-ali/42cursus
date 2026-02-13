/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
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
	ft_print_debug("DEBUG: starting parse_nodes recursion\n");
	parse_nodes(ctx->fd, (uint64_t)-1, ctx->version >= 7500, &ctx->data);
	close(ctx->fd);
	ctx->fd = -1;
	ft_print_debug("DEBUG: parse_nodes finished. counts: vc=%u nc=%u\n",
		ctx->data.vc, ctx->data.nc);
	if (!ctx->data.v || !ctx->data.ri)
	{
		fprintf(stderr, "Error: FBX missing critical data\n");
		return (false);
	}
	if (ctx->data.vc > 1000000)
	{
		fprintf(stderr, "Error: FBX mesh too large (%d vertices, limit 1M)\n",
			ctx->data.vc);
		return (false);
	}
	return (true);
}

bool		fbx_bin_build_mesh(t_fbx_bin_ctx *ctx);

bool	parse_fbx_binary(const char *path, t_scene *scene)
{
	t_fbx_bin_ctx	ctx;

	ft_print_debug("DEBUG: parse_fbx_binary starting for %s\n", path);
	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.fd = -1;
	if (!fbx_bin_open(&ctx, path))
		return (false);
	ft_print_debug("DEBUG: FBX Binary Version: %u\n", ctx.version);
	if (!fbx_bin_parse(&ctx))
	{
		fbx_bin_free_data(&ctx);
		free(ctx.mesh.base.name);
		return (false);
	}
	if (!fbx_bin_build_mesh(&ctx))
	{
		mesh_free(&ctx.mesh.base);
		return (false);
	}
	ft_print_debug("FBX Binary Loaded: %s (%d tris)\n", path,
		ctx.mesh.base.tri_count);
	return (scene_add_animated(scene, ctx.mesh));
}
