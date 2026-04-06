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

#include "fbx.h"

static void	parse_nodes_depth(t_fbx_parse *fbx, size_t end_offset,
				int depth);

static void	parse_array_bin(t_fbx_parse *fbx, t_fbx_array_req *req,
		int depth)
{
	(void)depth;
	ft_print_debug("   Depth %d: Reading %s...\n", depth, req->label);
	*req->dst = read_fbx_array(fbx->fd, req->count, req->elem_sz);
	if (!*req->dst)
		return ;
	if (req->div > 1)
	{
		ft_print_debug("   Depth %d: Got %s: %zu floats\n", depth, req->label,
			*req->count);
		*req->count /= req->div;
		return ;
	}
	ft_print_debug("   Depth %d: Got %s: %zu\n", depth,
		req->label, *req->count);
}

static void	parse_node_data(t_fbx_parse *fbx, t_fbx_bin_node *n, int depth)
{
	t_fbx_array_req	req;

	if (ft_strcmp(n->name, "Vertices") == 0 && !fbx->d->v)
		req = (t_fbx_array_req){"Vertices", (void **)&fbx->d->v, &fbx->d->rv.y, 8,
			3};
	else if (ft_strcmp(n->name, "PolygonVertexIndex") == 0 && !fbx->d->ri)
		req = (t_fbx_array_req){"Indices", (void **)&fbx->d->ri, &fbx->d->rv.x, 4,
			1};
	else if (ft_strcmp(n->name, "Normals") == 0 && !fbx->d->vn)
		req = (t_fbx_array_req){"Normals", (void **)&fbx->d->vn, &fbx->d->nu.x, 8,
			3};
	else if (ft_strcmp(n->name, "UV") == 0 && !fbx->d->vu)
		req = (t_fbx_array_req){"UVs", (void **)&fbx->d->vu, &fbx->d->nu.y, 8, 2};
	else
	{
		skip_properties(fbx->fd, n->num_properties);
		if ((size_t)lseek(fbx->fd, 0, SEEK_CUR) < n->end_offset)
			parse_nodes_depth(fbx, n->end_offset, depth + 1);
		return ;
	}
	parse_array_bin(fbx, &req, depth);
}

static void	parse_nodes_depth(t_fbx_parse *fbx, size_t end_offset,
		int depth)
{
	t_fbx_bin_node	n;

	if (depth > 20)
		return ;
	while ((size_t)lseek(fbx->fd, 0, SEEK_CUR) < end_offset)
	{
		read_node_header(fbx->fd, &n, fbx->is_64);
		if (n.end_offset == 0)
			break ;
		parse_node_data(fbx, &n, depth);
		if (lseek(fbx->fd, (off_t) n.end_offset, SEEK_SET) == (off_t) - 1)
			break ;
	}
}

void	parse_nodes(int fd, size_t end_offset, bool is_64, t_fbx_data *d)
{
	t_fbx_parse	fbx;

	fbx.fd = fd;
	fbx.is_64 = is_64;
	fbx.d = d;
	parse_nodes_depth(&fbx, end_offset, 0);
}
