/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:14:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static void	parse_nodes_depth(t_fbx_parse *fbx, size_t end_offset,
				int depth);

static void	parse_node_data(t_fbx_parse *fbx, t_fbx_bin_node *n, int depth)
{
	t_fbx_array_req	req;

	if (ft_strcmp(n->name, "Vertices") == 0 && !fbx->d->v)
		set_req(&req, fbx->d, FBX_TYPE_VERTICES);
	else if (ft_strcmp(n->name, "PolygonVertexIndex") == 0 && !fbx->d->ri)
		set_req(&req, fbx->d, FBX_TYPE_INDICES);
	else if (ft_strcmp(n->name, "Normals") == 0 && !fbx->d->vn)
		set_req(&req, fbx->d, FBX_TYPE_NORMALS);
	else if (ft_strcmp(n->name, "UV") == 0 && !fbx->d->vu)
		set_req(&req, fbx->d, FBX_TYPE_UVS);
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
