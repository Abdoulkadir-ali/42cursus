/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_positions(t_json_value *json, char *bin, t_mesh *m,
				int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;

	glb_parse_accessor(json, acc_idx, &acc);
	m->base_geometry.vertex_count = acc.count;
	m->base_geometry.vertices = malloc(sizeof(t_vec3) * acc.count);
	m->geometry.vertices = malloc(sizeof(t_vec3) * acc.count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data((t_extract){bin, &acc, &bv, m->base_geometry.vertices,
		sizeof(t_vec3), sizeof(t_vec3), sizeof(t_vec3), acc.count});
	ft_memcpy(m->geometry.vertices, m->base_geometry.vertices,
		sizeof(t_vec3) * acc.count);
}

static void	load_normals(t_json_value *json, char *bin, t_mesh *m, int acc_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;

	if (acc_idx < 0)
		return ;
	glb_parse_accessor(json, acc_idx, &acc);
	m->base_normals = malloc(sizeof(t_vec3) * acc.count);
	m->normals = malloc(sizeof(t_vec3) * acc.count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data((t_extract){bin, &acc, &bv, m->base_normals,
		sizeof(t_vec3), sizeof(t_vec3), sizeof(t_vec3), acc.count});
	ft_memcpy(m->normals, m->base_normals, sizeof(t_vec3) * acc.count);
}

/**
 * Loads vertex attributes (positions, normals, etc.) for a GLB mesh primitive.
 */
void	glb_load_attributes(t_mesh *mesh, t_json_value *json, char *bin,
			t_json_value *attr)
{
	load_positions(json, bin, mesh, json_get_size_t(attr, "POSITION", NULL));
	load_normals(json, bin, mesh, json_get_size_t(attr, "NORMAL", NULL));
}
