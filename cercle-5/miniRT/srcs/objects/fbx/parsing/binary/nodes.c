/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	parse_nodes_depth(t_fbx_parse_ctx *ctx, uint64_t end_offset,
				int depth);

static void	parse_array_bin(t_fbx_parse_ctx *ctx, t_fbx_array_req *req,
		int depth)
{
	(void)depth;
	ft_print_debug("   Depth %d: Reading %s...\n", depth, req->label);
	*req->dst = read_fbx_array(ctx->fd, req->count, req->elem_sz);
	if (!*req->dst)
		return ;
	if (req->div > 1)
	{
		ft_print_debug("   Depth %d: Got %s: %u floats\n", depth, req->label,
			*req->count);
		*req->count /= req->div;
		return ;
	}
	ft_print_debug("   Depth %d: Got %s: %u\n", depth, req->label, *req->count);
}

static void	parse_node_data(t_fbx_parse_ctx *ctx, t_fbx_bin_node *n, int depth)
{
	t_fbx_array_req	req;

	if (ft_strcmp(n->name, "Vertices") == 0 && !ctx->d->v)
		req = (t_fbx_array_req){"Vertices", (void **)&ctx->d->v, &ctx->d->vc, 8,
			3};
	else if (ft_strcmp(n->name, "PolygonVertexIndex") == 0 && !ctx->d->ri)
		req = (t_fbx_array_req){"Indices", (void **)&ctx->d->ri, &ctx->d->rc, 4,
			1};
	else if (ft_strcmp(n->name, "Normals") == 0 && !ctx->d->vn)
		req = (t_fbx_array_req){"Normals", (void **)&ctx->d->vn, &ctx->d->nc, 8,
			3};
	else if (ft_strcmp(n->name, "UV") == 0 && !ctx->d->vu)
		req = (t_fbx_array_req){"UVs", (void **)&ctx->d->vu, &ctx->d->uc, 8, 2};
	else
	{
		skip_properties(ctx->fd, n->num_properties);
		if ((uint64_t)lseek(ctx->fd, 0, SEEK_CUR) < n->end_offset)
			parse_nodes_depth(ctx, n->end_offset, depth + 1);
		return ;
	}
	parse_array_bin(ctx, &req, depth);
}

static void	parse_nodes_depth(t_fbx_parse_ctx *ctx, uint64_t end_offset,
		int depth)
{
	t_fbx_bin_node	n;

	if (depth > 20)
		return ;
	while ((uint64_t)lseek(ctx->fd, 0, SEEK_CUR) < end_offset)
	{
		read_node_header(ctx->fd, &n, ctx->is_64);
		if (n.end_offset == 0)
			break ;
		parse_node_data(ctx, &n, depth);
		if (lseek(ctx->fd, (off_t) n.end_offset, SEEK_SET) == (off_t) - 1)
			break ;
	}
}

void	parse_nodes(int fd, uint64_t end_offset, bool is_64, t_fbx_data *d)
{
	t_fbx_parse_ctx	ctx;

	ctx.fd = fd;
	ctx.is_64 = is_64;
	ctx.d = d;
	parse_nodes_depth(&ctx, end_offset, 0);
}
