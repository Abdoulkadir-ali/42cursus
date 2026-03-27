/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 21:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Binary FBX array dispatcher. Updates t_fbx internal buffers.
 */
static void	p_arr(t_fbx *fbx, void **dst, uint32_t *cnt, int sz)
{
	*dst = read_fbx_array(fbx->fd, cnt, sz);
}

/**
 * @brief Matches node name and populates internal fbx arrays.
 */
static void	p_data(t_fbx *f, t_fbx_bin_node *n)
{
	if (ft_strcmp(n->name, "Vertices") == 0 && f->v == NULL)
		p_arr(f, (void **)&f->v, &f->vc, 8);
	else if (ft_strcmp(n->name, "PolygonVertexIndex") == 0 && f->ri == NULL)
		p_arr(f, (void **)&f->ri, &f->rc, 4);
	else if (ft_strcmp(n->name, "Normals") == 0 && f->vn == NULL)
		p_arr(f, (void **)&f->vn, &f->nc, 8);
	else if (ft_strcmp(n->name, "UV") == 0 && f->vu == NULL)
		p_arr(f, (void **)&f->vu, &f->uc, 8);
	else
		fbx_skip_props(f->fd, n->num_properties);
}

/**
 * @brief Hierarchical node parser.
 */
static void	p_node(t_fbx *f, uint64_t end, int d)
{
	t_fbx_bin_node	n;

	if (d > 20)
		return ;
	while ((uint64_t)lseek(f->fd, 0, SEEK_CUR) < end)
	{
		fbx_read_header(f->fd, &n, f->is_64);
		if (n.end_offset == 0)
			break ;
		p_data(f, &n);
		if ((uint64_t)lseek(f->fd, 0, SEEK_CUR) < n.end_offset)
			p_node(f, n.end_offset, d + 1);
		lseek(f->fd, (off_t)n.end_offset, SEEK_SET);
	}
}

/**
 * @brief Public interface for FBX Binary node extraction.
 */
void	fbx_parse_nodes(t_fbx *f, uint64_t end)
{
	p_node(f, end, 0);
}
