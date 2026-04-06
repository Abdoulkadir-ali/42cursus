/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	widen_indices(size_t *dst, unsigned char *src, size_t count,
				int comp_type)
{
	size_t	i;

	i = 0;
	if (comp_type == 5123)
		while (i < count)
		{
			dst[i] = ((unsigned short *)src)[i];
			i++;
		}
	else if (comp_type == 5125)
		while (i < count)
		{
			dst[i] = ((unsigned int *)src)[i];
			i++;
		}
	else
		while (i < count)
		{
			dst[i] = src[i];
			i++;
		}
}

static void	load_indices(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	unsigned char	*src;

	if (acc_idx < 0)
	{
		m->base_geometry.indices = NULL;
		m->base_geometry.index_count = 0;
		return ;
	}
	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	m->base_geometry.index_count = acc.count;
	m->base_geometry.indices = malloc(sizeof * acc.count);
	if (!m->base_geometry.indices)
		return ;
	ft_memset(m->base_geometry.indices, 0, sizeof * acc.count);
	src = (unsigned char *)(bin + bv.byte_offset + acc.byte_offset);
	widen_indices(m->base_geometry.indices, src, acc.count, acc.component_type);
}

/**
 * Loads a GLB mesh primitive into the engine's internal mesh structure.
 */
void	glb_load_mesh(t_mesh *mesh, t_json_value *json, char *bin,
				size_t mesh_idx)
{
	t_json_value	*m;
	t_json_value	*prim;
	t_index			idx;

	m = json_at(json_get(json, "meshes"), mesh_idx);
	if (!m)
		return ;
	prim = json_at(json_get(m, "primitives"), 0);
	if (!prim)
		return ;
	glb_load_attributes(mesh, json, bin, json_get(prim, "attributes"));
	idx = json_get_size_t(prim, "indices");
	if (!idx.error)
		load_indices(json, bin, mesh, idx.i);
}
