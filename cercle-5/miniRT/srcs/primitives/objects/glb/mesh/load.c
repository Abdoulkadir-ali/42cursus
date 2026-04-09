/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:00:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	widen_indices(size_t *dst, unsigned char *src, size_t count,
				int comp_type)
{
	size_t	i;

	i = 0;
	if (comp_type == GLB_TYPE_UNSIGNED_SHORT)
		while (i < count)
			dst[i] = ((unsigned short *)src)[i];
	else if (comp_type == GLB_TYPE_UNSIGNED_INT)
		while (i < count)
			dst[i] = ((unsigned int *)src)[i];
	else
		while (++i < count)
			dst[i] = src[i];
}

static void	load_indices(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*src;
	size_t			sz;

	if (acc_idx < 0)
	{
		m->base_geometry.indices = NULL;
		m->base_geometry.index_count = 0;
		return ;
	}
	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	m->base_geometry.index_count = acc.count;
	sz = sizeof(*m->base_geometry.indices) * acc.count;
	m->base_geometry.indices = malloc(sz);
	if (!m->base_geometry.indices)
		return ;
	ft_memset(m->base_geometry.indices, 0, sz);
	src = (unsigned char *)(bin + bv.byte_offset + acc.byte_offset);
	widen_indices(m->base_geometry.indices, src, acc.count, acc.component_type);
}

void	glb_load_mesh(t_mesh *mesh, t_json_value *json, char *bin,
				size_t mesh_idx)
{
	t_json_value	*mj;
	t_json_value	*p;
	t_index			idx;

	mj = json_at(json_get(json, "meshes"), mesh_idx);
	if (!mj)
		return ;
	p = json_at(json_get(mj, "primitives"), 0);
	if (!p)
		return ;
	glb_load_attributes(mesh, json, bin, json_get(p, "attributes"));
	idx = json_get_size_t(p, "indices");
	if (!idx.error)
		load_indices(json, bin, mesh, idx.i);
}
