/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_indices(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;

	if (acc_idx < 0)
	{
		m->base_geometry.indices = NULL;
		m->base_geometry.index_count = 0;
		return ;
	}
	glb_parse_accessor(json, acc_idx, &acc);
	m->base_geometry.index_count = acc.count;
	m->base_geometry.indices = malloc(sizeof(size_t) * acc.count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data((t_extract){bin, &acc, &bv, m->base_geometry.indices,
		sizeof(size_t), sizeof(size_t), sizeof(size_t), acc.count});
}

/**
 * Loads a GLB mesh primitive into the engine's internal mesh structure.
 */
void	glb_load_mesh(t_mesh *mesh, t_json_value *json, char *bin,
			int mesh_idx)
{
	t_json_value	*m;
	t_json_value	*prim;

	m = json_at(json_get(json, "meshes"), mesh_idx);
	if (!m)
		return ;
	prim = json_at(json_get(m, "primitives"), 0);
	if (!prim)
		return ;
	glb_load_attributes(mesh, json, bin, json_get(prim, "attributes"));
	load_indices(json, bin, mesh, json_get_size_t(prim, "indices", NULL));
}
