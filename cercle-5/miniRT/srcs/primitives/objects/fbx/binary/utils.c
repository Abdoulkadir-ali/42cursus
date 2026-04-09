/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:13:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:13:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static void	set_req_geom(t_fbx_array_req *req, t_fbx_data *d, t_fbx_type type)
{
	if (type == FBX_TYPE_VERTICES)
	{
		req->label = "Vertices";
		req->dst = (void **)&d->v;
		req->count = &d->rv.y;
		req->elem_sz = 8;
		req->div = 3;
	}
	else if (type == FBX_TYPE_INDICES)
	{
		req->label = "Indices";
		req->dst = (void **)&d->ri;
		req->count = &d->rv.x;
		req->elem_sz = 4;
		req->div = 1;
	}
}

void	set_req(t_fbx_array_req *req, t_fbx_data *d, t_fbx_type type)
{
	if (type < 2)
		set_req_geom(req, d, type);
	else if (type == FBX_TYPE_NORMALS)
	{
		req->label = "Normals";
		req->dst = (void **)&d->vn;
		req->count = &d->nu.x;
		req->elem_sz = 8;
		req->div = 3;
	}
	else if (type == FBX_TYPE_UVS)
	{
		req->label = "UVs";
		req->dst = (void **)&d->vu;
		req->count = &d->nu.y;
		req->elem_sz = 8;
		req->div = 2;
	}
}

void	parse_array_bin(t_fbx_parse *fbx, t_fbx_array_req *req,
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
