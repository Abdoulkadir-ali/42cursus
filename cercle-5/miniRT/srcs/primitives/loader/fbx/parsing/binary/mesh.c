/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 04:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static bool	fbx_bin_set_vertices(t_fbx_bin_ctx *ctx)
{
	ctx->mesh.base.vertices = repack_doubles_to_vec3((double *)ctx->data.v,
			ctx->data.vc);
	free(ctx->data.v);
	ctx->data.v = NULL;
	if (!ctx->mesh.base.vertices)
		return (false);
	return (true);
}

static void	fbx_bin_set_normals(t_fbx_bin_ctx *ctx)
{
	t_vec3	*rn;

	if (!ctx->data.vn)
		return ;
	rn = repack_doubles_to_vec3((double *)ctx->data.vn, ctx->data.nc);
	free(ctx->data.vn);
	ctx->data.vn = rn;
}

static void	fbx_bin_fill_args(t_fbx_flat_args *p, t_fbx_data *d)
{
	p->raw = d->ri;
	p->raw_c = (int)d->rc;
	p->n = d->vn;
	p->nc = (int)d->nc;
	p->u = d->vu;
	p->uc = (int)d->uc;
	p->vc = (int)d->vc;
}

static void	fbx_bin_release_arrays(t_fbx_bin_ctx *ctx)
{
	if (ctx->data.vn)
		free(ctx->data.vn);
	if (ctx->data.vu)
		free(ctx->data.vu);
	if (ctx->data.ri)
		free(ctx->data.ri);
}

bool	fbx_bin_build_mesh(t_fbx_bin_ctx *ctx)
{
	t_fbx_flat_args	p;

	if (!fbx_bin_set_vertices(ctx))
		return (false);
	fbx_bin_set_normals(ctx);
	fbx_bin_fill_args(&p, &ctx->data);
	ft_print_debug("DEBUG: calling fbx_build_flat\n");
	fbx_build_flat(&ctx->mesh.base, &p);
	ft_print_debug("DEBUG: fbx_build_flat finished\n");
	fbx_bin_release_arrays(ctx);
	if (ctx->mesh.base.tri_count == 0)
		return (false);
	return (true);
}
